import numpy as np
import argparse
import json

### Convert .csv files from Geoneutrinos.org into ratdb files to be read in by
### the IBD generator.

def getargs():
    parser = argparse.ArgumentParser()
    parser.add_argument('incsv', type=str)
    parser.add_argument('--out', '-o', default='output.ratdb')
    parser.add_argument('--comp', default='total', choices=['total', 'geo', 'reactor', 'closest'])
    parser.add_argument('--comment', type=str)
    parser.add_argument('--index', type=str, default='default')
    parser.add_argument('--plot', action='store_true')
    return parser.parse_args()

def main():
    args = getargs()
    total, iaea, close, user, geo_u, geo_th = \
        np.loadtxt( args.incsv, skiprows=1, delimiter=',', unpack=True )
    ## From geonu docs, bin centers from 1.805 to 9.995
    energy = np.linspace(1.805, 9.995, 820)
    flux = total
    if args.comp == 'geo':
        flux = geo_u + geo_th
    if args.comp == 'reactor':
        flux = iaea
    if args.comp == 'closest':
        flux = close

    binwidth = np.mean( np.diff(energy) ) * 1000 # MeV to keV
    integratedFlux = np.sum(flux)*binwidth
    print(f'Binwidth: {binwidth}')
    print(f'Integrated Flux: {integratedFlux}')

    with open(args.out, 'w') as ff:
        ff.write(f'// {args.comment}\n')
        ff.write(f'// Integrated Flux: {integratedFlux}\n')
        ff.write('{\n')
        ff.write('name: "IBD",\n')
        ff.write(f'index: "{args.index}",\n')
        ff.write('run_range: [0, 0],\n\n')
        ff.write('emin: 1.805,\n')
        ff.write('emax: 9.995,\n\n')
        ff.write(f'spec_e: {np.array2string(energy, max_line_width=1000000, separator=",")},\n')
        ff.write(f'spec_flux: {np.array2string(flux, max_line_width=1000000, separator=",")},\n')
        ff.write('}\n\n')

    if args.plot:
        import matplotlib.pyplot as plt
        plt.step(energy, flux, where='mid', label=f'{args.index}: {integratedFlux} TNU')
        plt.ylim(bottom=0)
        plt.xlim(0, max(energy))
        plt.xlabel("Antineutrino energy (MeV)")
        plt.ylabel("TNU / keV")
        plt.legend()
        plt.show()


if __name__ == '__main__':
    main()
