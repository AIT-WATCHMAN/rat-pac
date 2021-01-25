'''Create a PMTINFO RATDB table with positions of PMTs arranged in a box.
Must be run from the util folder. Will create a files in the data folder.
'''
import numpy as np
import math
import os

### Default values to change ratdb geometry files

#rPMT    = 6700.0
rPMT    = 5065.0
#rPMT    = 4065.0
rPMT    = 5465.0
#rPMT    = 4465.0

#zPMT    = 6700.0
zPMT    = 5065.0
#zPMT    = 4065.0
zPMT    = 5465.0
#zPMT    = 4465.0

dFIDVol = -150.0 ## Arbitrary 1m buffer
tFIDVol = 0.0
dPSUP   = 385    
tPSUP   = 10.0
tBSHEET = 5.0
#dTANK   = 935.0
dTANK   = 535.0  
tTANK   = 400.0
dAIR    = 1000.0 
dCONC   = 500.0
tCONC   = 25000.0
dROCK   = 2000.0  


## Values to change for PMT arrangement. (PMTINFO)
photocoverage = 0.105
photocoverage = 0.155
photocoverage = 0.205
pmtRad        = 126.5


def geoFile(rPMT = 3498.125,  zPMT = 3498.125,\
dFIDVol = -1000.0,\
tFIDVol = 0.0,\
dPSUP   = 100.0,\
tPSUP   = 10.0,\
tBSHEET = 5.0,\
dTANK   = 501.875,    
tTANK   = 500.0,\
dAIR    = 1000.0 ,\
dCONC   = 500.0,\
tCONC   = 25000.0,\
dROCK   = 2000.0,\
pmtCnt  =  4000.0   ):                            
## dtank With respect to PMTs

    return  f"""{{
name: "GEO",
index: "world",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "", // world volume has no mother
type: "box",
size: [10000.0, 10000.0, 300000.0], // mm, half-length
material: "air", //rock?
invisible: 1,
}}

///////////////////// Define the rock volumes. Thin slab of rock is assumed ////////////////////////

//Create a 1-m rock layer around a cylindrical cavern
{{
name: "GEO",
index: "rock_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "world", // world volume has no mother
//type: "box",
//size: [7000.0, 27000.0, 7000.0], // mm, half-length
//size: [{rPMT+dTANK+dAIR+dROCK}, {+dTANK+dAIR+dROCK}, {zPMT+dTANK+dAIR+dROCK}],
type: "tube",
r_max: {rPMT+dTANK+dAIR+dROCK}, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: {zPMT+dTANK+dAIR+dROCK},
position: [0.0, 0.0, 0.0], //this will allow for the concrete layer on the floor and not on the ceiling
material: "rock",
invisible: 1,
//color: [1.0,0.6,0.0,1.0],
//drawstyle: "solid"
}}


//Create a 0.5m concrete layer on the walls and base
{{
name: "GEO",
index: "concrete",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "rock_1",
//type: "box",
//size: [5500.0, 26500.0, 5500.0], // mm, half-length
//size: [{rPMT+dTANK+dAIR+dCONC}, {+dTANK+dAIR+dCONC}, {zPMT+dTANK+dAIR+dCONC}], 
type: "tube",
r_max: {rPMT+dTANK+dAIR+dCONC}, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: {zPMT+dTANK+dAIR+dCONC},
position: [0.0, 0.0, 0.0], // this will give a concrete layer on the floor and not on the ceiling
material: "concrete", // changed from "gunite" (L. Kneale)
invisible: 1,
//color: [0.8,0.8,0.8,0.8],
//drawstyle: "solid"
}}
//Create the cavern space between the tank and concrete
{{
name: "GEO",
index: "cavern",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "concrete",
//type: "box",
//size: [5000.0, 26000.0, 5000.0], // mm, half-length
//size: [{rPMT+dTANK+dAIR}, {+dTANK+dAIR}, {zPMT+dTANK+dAIR}], 
type: "tube",
r_max: {rPMT+dTANK+dAIR}, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: {zPMT+dTANK+dAIR},
position: [0.0, 0.0, 0.0],
material: "air",
invisible: 1,
}}
////////////////////////////////// Define the rock volumes done.///////////////////////////////////
{{
name: "GEO",
index: "tank",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "cavern",
//type: "box",
//size: [4500.0, 24500.0, 4500.0], // mm, half-length
//size: [{rPMT+dTANK}, {+dTANK}, {zPMT+dTANK}], 
type: "tube",
r_max: {rPMT+dTANK}, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: {zPMT+dTANK},
position: [0.0, 0.0, 0.0],
material: "stainless_steel",
color: [0.6,0.6,0.9,0.01],
drawstyle: "solid"
}}
{{
name: "GEO",
index: "detector_veto1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "tank",
//type: "box",
//size: [4498.125, 24498.125, 4498.125], // mm, half-length
//size: [{rPMT+dTANK-tTANK}, {+dTANK-tTANK}, {zPMT+dTANK-tTANK}],
type: "tube",
r_max: {rPMT+dTANK-tTANK}, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: {zPMT+dTANK-tTANK},
position: [0.0, 0.0, 0.0],
material: "doped_water",
color: [0.2,0.2,0.9,0.2],
drawstyle: "solid"
}}
{{
name: "GEO",
index: "psup",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector_veto1",
//type: "box",
//size: [4498.125, 24498.125, 4498.125], // mm, half-length
//size: [{rPMT+dPSUP+tPSUP}, {+dPSUP+tPSUP}, {zPMT+dPSUP+tPSUP}],
type: "tube",
r_max: {rPMT+dPSUP+tPSUP}, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: {zPMT+dPSUP+tPSUP},
position: [0.0, 0.0, 0.0],
material: "stainless_steel",
color: [0.2,0.2,0.9,0.2],
drawstyle: "solid"
}}
{{
name: "GEO",
index: "detector_veto2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "psup",
//type: "box",
//size: [4498.125, 24498.125, 4498.125], // mm, half-length
//size: [{rPMT+dPSUP}, {+dPSUP}, {zPMT+dPSUP}],
type: "tube",
r_max: {rPMT+dPSUP}, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: {zPMT+dPSUP},
position: [0.0, 0.0, 0.0],
material: "doped_water",
color: [0.2,0.2,0.9,0.2],
drawstyle: "solid"
}}
{{
name: "GEO",
index: "black_sheet",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector_veto2",
//type: "box",
//size: [3508.125, 23508.125, 3508.125], // mm, half-length
//size: [{rPMT+tBSHEET},{+tBSHEET},{zPMT+tBSHEET}],
type: "tube",
r_max: {rPMT+tBSHEET}, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: {zPMT+tBSHEET},
position: [0.0, 0.0, 0.0],
material: "polypropylene",
color: [0.,0.,0.,1.0],
drawstyle: "solid",
}}
{{
name: "GEO",
index: "detector_target_gb",// gb: gamma buffer
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "black_sheet",
//type: "box",
//size: [3498.125, 23498.125, 3498.125] // mm, half-length
//size: [{rPMT},{zPMT}],
type: "tube",
r_max: {rPMT}, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: {zPMT},
position: [0.0, 0.0, 0.0],
material: "doped_water",
color: [0.2,0.2,0.9,0.2],
drawstyle: "solid"
}}
{{
name: "GEO",
index: "detector_target_fv", // fv : fiducial volume
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector_target_gb", // gb : gamma buffer
//type: "box",
//size: [3498.125, 23498.125, 3498.125] // mm, half-length
//size: [{rPMT+dFIDVol},{+dFIDVol},{zPMT+dFIDVol}],
type: "tube",
r_max: {rPMT+dFIDVol}, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: {zPMT+dFIDVol},
position: [0.0, 0.0, 0.0],
material: "doped_water",
color: [0.2,0.2,0.9,0.2],
drawstyle: "solid"
}}
{{
//Bergevin: Set the interface were reflection can occur. Must make sure volume1 and volume2
//are in the correct order
name: "GEO",
index: "midsurface_black_sheet",
valid_begin: [0, 0],
valid_end: [0, 0],
invisible: 0, // omitted for visualization
mother: "black_sheet", //not used but needs to be a valid name, parent of 'a' and 'b' would be best choice
type: "border",
volume1: "detector_target_gb",
volume2: "black_sheet",
reverse: 1, //0 only considers photons from a->b, 1 does both directions
surface: "nonreflective_tarp",
}}

{{
name: "GEO",
index: "inner_pmts",
enable: 1,
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector_target_gb",
type: "pmtarray",
end_idx: {int(pmtCnt-1)}, //idx of the last pmt
start_idx: 0, //idx of the first pmt
pmt_model: "r7081pe",
mu_metal: 0,
mu_metal_material: "aluminum",
mu_metal_surface: "aluminum",
light_cone: 0,
light_cone_material: "aluminum",
light_cone_surface: "aluminum",
light_cone_length: 17.5,
light_cone_innerradius: 12.65,
light_cone_outerradius: 21,
light_cone_thickness: 0.2,
black_sheet_offset: 300.0, //30 cm default black tarp offset
black_sheet_thickness: 10.0, //1 cm default black tarp thickness
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner",
efficiency_correction: 0.90000,
pos_table: "PMTINFO", //generated by positions.nb
orientation: "manual",
orient_point: [0.,0.,0.],
color: [0.3,0.5, 0.0, 0.2],
}}
"""






def cylinder(rPMT,zPMT,_type=1,inv = 1.0, inner = 1.0,spacing = 500.,\
delta = 250.,tolerance = 200., photocoverage=0.205, pmtRad = 126.5):
    x,y,z,dx,dy,dz,type = [],[],[],[],[],[],[]
    cnt = 0 
    #top
    pmtArea = 3.14159265359*pmtRad*pmtRad
    length = int(np.sqrt(pmtArea/photocoverage))  
    print('Length/spacing: ',length,spacing) 
    spacing = length 
    rangeX = rangeY = int((2.0*rPMT)/spacing)
    height =  zPMT
    radius  = rPMT
    _cntB = 0
    for _i in range(rangeX):
        for _j in range(rangeY):
            _x,_y = (_i*spacing + delta),(_j*spacing + delta)
            if np.sqrt(_x*_x+_y*_y)< radius - tolerance:  #Asummes right cylinder such that Height = radius            
                x.append( _x)
                y.append( _y)
                x.append(-_x)
                y.append( _y)
                x.append( _x)
                y.append(-_y)
                x.append(-_x)
                y.append(-_y)
                cnt+=4
                _cntB+=4
    
    #z,dx,dy,dz,type = [],[],[],[],[]
    for i in range(_cntB):
        z.append(height)
        dx.append(0.0)
        dy.append(0.0)
        dz.append(-1.0*inv)
        type.append(_type)

    ##bottom
    _cntB = 0
    for _i in range(rangeX):
        for _j in range(rangeY):
            _x,_y = (_i*spacing + delta),(_j*spacing + delta)
            if np.sqrt(_x*_x+_y*_y)< radius -tolerance:  #Asummes right cylinder such that Height = radius
                x.append( _x)
                y.append( _y)
                x.append(-_x)
                y.append( _y)
                x.append( _x)
                y.append(-_y)
                x.append(-_x)
                y.append(-_y)
                cnt+=4
                _cntB+=4
    
    #z,dx,dy,dz,type = [],[],[],[],[]
    for i in range(_cntB):
        z.append(-height)
        dx.append(0.0)
        dy.append(0.0)
        dz.append(1.0*inv)
        type.append(_type)

    #side
    nRings  = int(np.round(( zPMT ) / length))
    collums = int(np.round(( 2.0 * math.pi * rPMT ) / length))
    
    _dTheta = 2.0 * math.pi / collums
    print('Collumns: ',collums,'\nNrings: ',nRings,'\ndelta Theta: ',_dTheta)
 
    for _i in range(nRings):
        #        print((_i*500.)+250.,-((_i*500.)+250.))
        for _j in range(collums):
            _theta,_z = _j*_dTheta,(_i*spacing)+delta
            
            x.append(radius * math.cos(_theta))
            y.append(radius * math.sin(_theta))
            z.append(_z)
            dx.append(-math.cos(_theta)*inv)
            dy.append(-math.sin(_theta)*inv)
            dz.append(0.0)
            type.append(_type)
            x.append(radius * math.cos(_theta))
            y.append(radius * math.sin(_theta))
            z.append(-_z)
            dx.append(-math.cos(_theta)*inv)
            dy.append(-math.sin(_theta)*inv)
            dz.append(0.0)
            type.append(_type)
            cnt+=2


#    print(cnt)
    return x,y,z,dx,dy,dz,type,cnt

def pmtinfoFile(_x=rPMT, _z=zPMT,\
photocoverage=photocoverage, pmtRad = pmtRad):

    x,y,z,dx,dy,dz,type,cnt = cylinder(rPMT,zPMT,photocoverage=photocoverage, pmtRad = pmtRad)
    
    pmt_info = "{\n"
    pmt_info += f"//// Total number of inner PMTs : {cnt}\n"
    pmt_info += f"//// Total number of veto PMTs : 0\n"
    pmt_info += f"\"name\": \"PMTINFO\",\n"
    pmt_info += f"\"valid_begin\": [0, 0],\n"
    pmt_info += f"\"valid_end\": [0, 0],\n"
    pmt_info += f"\"x\":     {x},\n"
    pmt_info += f"\"y\":     {y},\n"
    pmt_info += f"\"z\":     {z},\n"
    pmt_info += f"\"dir_x\": {dx},\n"
    pmt_info += f"\"dir_y\": {dy},\n"
    pmt_info += f"\"dir_z\": {dz},\n"
    pmt_info += f"\"type\":  {type},\n"
    pmt_info += "}"

    return pmt_info,cnt



#####  main code ###########

_pmtinfo,cnt = pmtinfoFile(_x=rPMT, _z=zPMT,\
photocoverage=photocoverage, pmtRad = pmtRad)

_geoFile = geoFile(rPMT = rPMT, zPMT = zPMT,dFIDVol = dFIDVol,tFIDVol = tFIDVol,dPSUP   = dPSUP,tPSUP = tPSUP,\
tBSHEET = tBSHEET, dTANK = dTANK,tTANK = tTANK,dAIR = dAIR ,dCONC = dCONC,tCONC = tCONC, dROCK = dROCK, pmtCnt = cnt )

#print(_geoFile)
#print()
#print(_pmtinfo)


try:
    os.mkdir(f"../data/Watchman_rightcylinder_{int((rPMT+dTANK)*2.0/1000)}m_{int((zPMT+dTANK)*2.0/1000)}m_{int(photocoverage*100)}pct")
    print('Created', f"../data/Watchman_rightcylinder_{int((rPMT+dTANK)*2.0/1000)}m_{int((zPMT+dTANK)*2.0/1000)}m_{int(photocoverage*100)}pct")
except OSError as error:  
    print(error)   

geofile = open(f"../data/Watchman_rightcylinder_{int((rPMT+dTANK)*2.0/1000)}m_{int((zPMT+dTANK)*2.0/1000)}m_{int(photocoverage*100)}pct/Watchman_rightcylinder_{int((rPMT+dTANK)*2.0/1000)}m_{int((zPMT+dTANK)*2.0/1000)}m_{int(photocoverage*100)}pct.geo","w+")
geofile.writelines(_geoFile)
geofile.close

pmtfile = open(f"../data/Watchman_rightcylinder_{int((rPMT+dTANK)*2.0/1000)}m_{int((zPMT+dTANK)*2.0/1000)}m_{int(photocoverage*100)}pct/PMTINFO.ratdb","w+")
pmtfile.writelines(_pmtinfo)
pmtfile.close


print("//// Total number of inner PMTs : ",cnt)
print("//// Photocoverage (%) : ",photocoverage*100.)
print("//// Detector height (m) : ",(zPMT+dTANK)*2.0/1000.)
print("//// Detector diamter (m) : ",(rPMT+dTANK)*2.0/1000.)
print("////")

