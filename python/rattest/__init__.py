import sys
import os.path
import shutil
import re
from math import sqrt

# ROOT changes into whatever directory it finds in the command line args
_argv = sys.argv
sys.argv = sys.argv[:1]
import ROOT
from ROOT import gROOT, gSystem, TFile, TH1, TCanvas, kRed, kBlue, kDashed
sys.argv = _argv

gROOT.SetBatch(True)
gROOT.ProcessLine(".x "+os.path.join(os.environ['RATROOT'], 'rootinit.C'))
TH1.SetDefaultSumw2()

### Other modules ###
import os.path
import re

def target_needs_update(target, sources):
    if not os.path.exists(target):
        return True
    else:
        target_date = os.path.getmtime(target)
        
    for source in sources:
        if target_date < os.path.getmtime(source):
            return True
    
    return False

def find_outfile_name(filename):
    f = file(filename).read()
    match = re.search(r'/rat/proc\soutroot\s/rat/procset\sfile\s"(.+)"', f)
    if match:
        return match.group(1)
    else:
        return None
        
def dir_to_strlist(directory):
    l = []
    for obj in directory.GetListOfKeys():
        l.append(obj.GetName())
    return l

class RatTest:
    def __init__(self, config_file):
        self.config_file = config_file
        self.testdir = os.path.abspath(os.path.dirname(config_file))
        # Create default name out of bottom level dir name
        self.name = os.path.basename(self.testdir)
        self.description = ''
        
        # Load testcase settings from file and store all attributes in this object
        params = {}
        execfile(self.config_file, {}, params)
        for k,v in params.items():
            setattr(self, k, v)
        
        # Expand full paths
        self.rat_macro = os.path.abspath(os.path.join(self.testdir, self.rat_macro))
        self.root_macro = os.path.abspath(os.path.join(self.testdir, self.root_macro))
        self.rat_bin = os.path.abspath(os.path.join(os.environ['RATROOT'],
                                                    'bin', 'rat'))
        
        # Find name of file holding events
        self.event_file = os.path.join(self.testdir, find_outfile_name(self.rat_macro))
        print 'Event file:', self.event_file
        
        # Generate names of standard and current output files
        self.standard_results = os.path.join(self.testdir, 'standard.root')
        self.current_results = os.path.join(self.testdir, 'current.root')

    def run(self, regen_mc=False, regen_plots=False, html=None):
        print '='*5, 'Run Test:', self.name, '='*5
        self._do_run(regen_mc=regen_mc, regen_plots=regen_plots)
        
        if html: html.header(name=self.name, description=self.description)
        
        return self.compare_hists(self.standard_results, self.current_results, html=html)

    def update(self, regen_mc=False, regen_plots=False):
        print '='*5, 'Update Test:', self.name, '='*5
        self._do_run(regen_mc=regen_mc, regen_plots=regen_plots)
        print 'Copying current results to master file of standard results'
        shutil.copyfile(self.current_results, self.standard_results)
        
    def _do_run(self, regen_mc, regen_plots):
        if regen_mc or target_needs_update(self.event_file, [self.rat_macro, self.rat_bin]):
            self.run_rat()
        if regen_plots or target_needs_update(self.current_results, [self.event_file, self.root_macro]):
            self.run_root()
            

    def run_rat(self):
        self.run_cmd_in_testdir('rat ' + os.path.basename(self.rat_macro))
        
    def run_root(self):
        cwd = os.getcwd()
        try:
            os.chdir(self.testdir)
            gSystem.ChangeDirectory(self.testdir)
            gROOT.ProcessLine('.L ' + os.path.basename(self.root_macro))
            event_file = TFile(self.event_file)
            event_tree = event_file.Get('T')
            outfile = TFile(self.current_results, 'RECREATE')
            outfile.cd()
            ROOT.make_plots(event_file, event_tree, outfile)

            outfile.Close()
            event_file.Close()
        finally:
            os.chdir(cwd)
            
    def run_cmd_in_testdir(self, cmd):
        cwd = os.getcwd()
        try:
            os.chdir(self.testdir)
            print 'Running:', cmd
            os.system(cmd)
        finally:
            os.chdir(cwd)
    
    def compare_hists(self, master_fname, current_fname,html=None):
        master_file = TFile(master_fname)
        current_file = TFile(current_fname)
        
        master_objs = set(dir_to_strlist(master_file))
        current_objs = set(dir_to_strlist(current_file))
        m_only = master_objs.difference(current_objs)
        both = master_objs.intersection(current_objs)
        c_only = current_objs.difference(master_objs)
        
        if len(m_only) != 0:
            print 'WARNING: master contains', ' '.join(m_only), 'and current test does not.'
        if len(c_only) != 0:
            print 'WARNING: current test file contains', ' '.join(list(c_only)), 'and master does not.'
            
        overall_success = True
        for objname in both:
            c_obj = current_file.Get(objname)
            m_obj = master_file.Get(objname)

            prob = m_obj.KolmogorovTest(c_obj)
            
            print "Comparing", objname, ":", c_obj.GetTitle()
            
            if prob > 0.01:
                print "  SUCCESS",
                success = True
            else:
                print "  FAILURE",
                overall_success = False
                success = False
            print ": KS prob =", prob
            
            plotfile = os.path.join(self.testdir, objname+'.png')
            self.draw_hist(plotfile, m_obj, c_obj)
            fit_parameters = self.get_fit(m_obj, c_obj)
            
            if html: html.hist(name=objname, description='', prob=prob,
                               success=success,
                               plotname=os.path.basename(plotfile),
                               parameters=fit_parameters)
        return overall_success
            
    def draw_hist(self, plotfile, master, current):
        c1 = TCanvas('c1', '', 600, 400)
        master.SetLineColor(kBlue)
        current.SetLineColor(kRed)
        current.SetLineStyle(kDashed)
        
        all_min = min(master.GetMinimum(), current.GetMinimum())
        all_max = max(master.GetMaximum(), current.GetMaximum())
        span = all_max - all_min
        master.SetMinimum(all_min - 0.1 * span)
        master.SetMaximum(all_max + 0.1 * span)
            
        master.Draw()
        current.Draw("SAME")
            
        c1.Print(plotfile)

    def get_fit(self, master_hist, current_hist):
        master_funclist = master_hist.GetListOfFunctions()
        current_funclist = current_hist.GetListOfFunctions()

        if master_funclist.GetSize() == 0 or current_funclist.GetSize() == 0:
            return None # Don't plot fit function parameters

        # Assume only 1 fit function
        master_func = master_funclist.At(0)
        current_func = current_funclist.At(0)

        # Make sure these are really functions
        if master_func.Class().GetName() != 'TF1' \
           or current_func.Class().GetName() != 'TF1':
            return None

        npar = master_func.GetNpar()
        parameters = []
        for ipar in xrange(npar):
            parameter = { 'name' : master_func.GetParName(ipar),
                          'm_val': master_func.GetParameter(ipar),
                          'm_err': master_func.GetParError(ipar),
                          'c_val': current_func.GetParameter(ipar),
                          'c_err': current_func.GetParError(ipar) }
            parameter['delta'] = parameter['c_val'] - parameter['m_val'] 
            parameter['sigma'] = abs(parameter['delta']) \
                                 / sqrt(parameter['m_err']**2 +
                                        parameter['c_err']**2)
            parameters.append(parameter)

        return parameters
            
        
class RatHtml:
    def __init__(self, htmlname):
        self.htmlname = htmlname
        self.plots = []
        
    def header(self, name, description):
        self.name = name
        self.description = description
    
    def hist(self, name, description, prob, success, plotname, parameters):
        p = {'name':name, 'description':description,
             'prob':prob, 'plotname' : plotname,
             'parameters': parameters}
        if success:
            p['result'] = '<font color="green">Success</font>'
        else:
            p['result'] = '<font color="red">Failure</font>'
        self.plots.append(p)
    
    def write(self):
        self.plots.sort(cmp=lambda x,y: cmp(x['name'], y['name']))
        
        f = file(self.htmlname, 'w')
        f.write(
'''
<html>
  <head>
    <title>RAT Test: %(name)s</title>
  </head>
  <body>
    <h1>RAT Test: %(name)s</h1>
    <p>%(description)s</p>
    
''' % { 'name' : self.name, 'description' : self.description})
        
        for p in self.plots:
            f.write(
'''
     <hr>
     <h3>%(name)s: %(result)s</h3>
     <p>%(description)s</p>
     <center>''' % p)

            f.write(
'''     <img src="%(plotname)s"><br>
     <font color="blue">Blue: Standard</font>,  <font color="red">Red: Current Code</font><br>
     <p>KS Probability: %(prob)f</p>''' % p)

            # Optional table showing fit parameters
            if p['parameters']:
                f.write('''
         <table border="1">
         <tr><th>Parameter Name</th><th>Standard</th><th>Current</th><th>Diff</th></tr>
''')
                for par in p['parameters']:
                    f.write('<tr><td>%(name)s</td><td>%(m_val)f (+/- %(m_err)1.3f)</td><td>%(c_val)f (+/- %(c_err)1.3f)</td><td>' % par)
                    if par['sigma'] > 2.0:
                        f.write('<font color="red">')
                    else:
                        f.write('<font color="green">')
                    f.write('%(sigma)1.1f&sigma;</font></td></tr>\n' % par)
                f.write('</table>\n')

            f.write('''
     </center>
''' % p
)

def make_template(testname):

    ## RAT test config
    f = open('rattest.config', 'w')
    f.write("""# -*- python-*-
description = '''Put your description here.'''
rat_macro = '%(testname)s.mac'
root_macro = '%(testname)s.C'
""" % { 'testname' : testname })
    f.close()

    ## RAT macro
    f = open('%s.mac' % (testname,), 'w')
    f.write('''
/glg4debug/glg4param omit_muon_processes  1.0
/glg4debug/glg4param omit_hadronic_processes  1.0

/rat/db/set DETECTOR experiment "cylinder"
/rat/db/set DETECTOR geo_file "cylinder/cylinder.geo"

/run/initialize

# BEGIN EVENT LOOP
/rat/proc count
/rat/procset update 5
/rat/proc outroot
/rat/procset file "%s.root"
# END EVENT LOOP

/generator/add combo gun:point
/generator/vtx/set e- 0 0 0 0.020
/generator/pos/set 0 0 0
/generator/rate/set 1

/run/beamOn 1000
''' % (testname,) )
    f.close()

    ## ROOT macro
    f = open('%s.C' % (testname,), 'w')
    f.write('''void make_plots(TFile *event_file, TTree *T, TFile *out_file)
{
  TH1F *hNumPE = new TH1F("hNumPE", "Number of photoelectrons/keV", 40, 1, 10);
  hNumPE->SetYTitle("Events per bin");
  hNumPE->SetXTitle("detected photoelectrons/keV");
  T->Draw("numPE/(mc.particle.ke*1000)>>hNumPE","","goff");
  hNumPE->Fit("gaus");
  hNumPE->Write();
}
''')
