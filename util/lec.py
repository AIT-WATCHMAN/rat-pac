'''Create a PMTINFO RATDB table with positions of PMTs arranged on a
cylinder.
'''

import numpy as np
import math


def square(_x=23498.125, _y=3498.125, _z=3498.125, photocoverage=0.205, pmtRad = 126.5):
    pmtArea = 3.14159265359*pmtRad*pmtRad
    length = np.sqrt(pmtArea/photocoverage)
   

    _nXCorr = 2.0*_x/length/np.round(2.0*_x/length)
    _nYCorr = 2.0*_y/length/np.round(2.0*_y/length)
    _nZCorr = 2.0*_z/length/np.round(2.0*_z/length)

 
    nX = int(np.round(2.0*_x/length))
    nY = int(np.round(2.0*_y/length))
    nZ = int(np.round(2.0*_z/length)) 
    
    cnt = 0
    x,y,z,dx,dy,dz,type = [],[],[],[],[],[],[]
    
    xEven = (nX%2==0)
    yEven = (nY%2==0)
    zEven = (nZ%2==0)
    print('//Length:',length, '(nX,nY,nZ):',nX, nY, nZ, 'Even:', xEven, yEven, zEven,'lengthCorrection:',_nXCorr, _nYCorr,_nZCorr)
    
    _lx = -_x + length/2.0*_nXCorr
    _ly = -_y + length/2.0*_nYCorr
    
    for __x in range(nX-2):
        _lx += length*_nXCorr
        _ly = -_y + length/2.0*_nYCorr
        for __y in range(nY-2):
            _ly += length*_nYCorr 
            x.append(_lx)
            y.append(_ly)
            z.append(_z)
            dx.append(0.0)
            dy.append(0.0)
            dz.append(-1.0)
            type.append(1)
            x.append(_lx)
            y.append(_ly)
            z.append(-_z)
            dx.append(0.0)
            dy.append(0.0)
            dz.append(1.0)
            type.append(1)
            cnt+=2
            #print( '(',__x,  __y,'): (',_lx,_ly,_z,')',length) 
            #print( '(',__x,  __y,'): (',_lx,_ly,-_z,')',length)


    _lx = -_x + length/2.0*_nXCorr
    _lz = -_z + length/2.0*_nZCorr

    for __x in range(nX-2):
        _lx += length*_nXCorr
        _lz = -_z + length/2.0*_nZCorr
        for __z in range(nZ-2):
            _lz += length*_nZCorr
            x.append(_lx)
            y.append(_y)
            z.append(_lz)
            dx.append(0.0)
            dy.append(-1.0)
            dz.append(0.0)
            type.append(1)
            x.append(_lx)
            y.append(-_y)
            z.append(_lz)
            dx.append(0.0)
            dy.append(1.0)
            dz.append(0.0)
            type.append(1)
            cnt+=2
            #print( '(',__x,  __y,'): (',_lx,_ly,_z,')',length) 
            #print( '(',__x,  __y,'): (',_lx,_ly,-_z,')',length)
    

    _ly = -_y + length/2.0*_nYCorr
    _lz = -_z + length/2.0*_nZCorr

    for __y in range(nY-2):
        _ly += length*_nYCorr
        _lz = -_z + length/2.0*_nZCorr
        for __z in range(nZ-2):
            _lz += length*_nZCorr
            x.append(_x)
            y.append(_ly)
            z.append(_lz)
            dx.append(-1.0)
            dy.append(0.0)
            dz.append(0.0)
            type.append(1)
            x.append(-_x)
            y.append(_ly)
            z.append(_lz)
            dx.append(1.0)
            dy.append(0.0)
            dz.append(0.0)
            type.append(1)
            cnt+=2
            #print( '(',__x,  __y,'): (',_lx,_ly,_z,')',length) 
            #print( '(',__x,  __y,'): (',_lx,_ly,-_z,')',length)

    
    return x,y,z,dx,dy,dz,type,cnt




#x_t,y_t,z_t,dx_t,dy_t,dz_t,type_t,cnt_t = topcap(6700.,13,13,1)
#x_b,y_b,z_b,dx_b,dy_b,dz_b,type_b,cnt_b = bottomcap(6700.,13,13,1)
#x_s,y_s,z_s,dx_s,dy_s,dz_s,type_s,cnt_s = sidePMTs(6700.,84,13,1)
#
#x_tv,y_tv,z_tv,dx_tv,dy_tv,dz_tv,type_tv,cnt_tv = topcap(   7200.,5,5,2,-1, 0,spacing = 1370.,delta = 685.)
#x_bv,y_bv,z_bv,dx_bv,dy_bv,dz_bv,type_bv,cnt_bv = bottomcap(7200.,5,5,2,-1,   spacing = 1370.,delta = 685.)
#x_sv,y_sv,z_sv,dx_sv,dy_sv,dz_sv,type_sv,cnt_sv = sidePMTs( 7200.,14,5,2,-1,  spacing = 1370.,delta = 685.)

x_t,y_t,z_t,dx_t,dy_t,dz_t,type_t,cnt_t = square()

print("////",cnt_t)
print("{")
print("//// Total number of inner PMTs : ",cnt_t)
print("//// Total number of veto PMTs : ",0)
print("\"name\": \"PMTINFO\",")
print("\"valid_begin\": [0, 0],")
print("\"valid_end\": [0, 0],")
print("\"x\":"    ,x_t,",")
print("\"y\":"    ,y_t,",")
print("\"z\":"    ,z_t,",")
print("\"dir_x\":",dx_t,",")
print("\"dir_y\":",dy_t,",")
print("\"dir_z\":",dz_t,",")
print("\"type\":",type_t,",")
print("}\n\n")

#print("////",cnt_tv,cnt_bv,cnt_sv)
#print("{")
#print("\"name\": \"PMTINFO\",")
#print("\"valid_begin\": [0, 0],")
#print("\"valid_end\": [0, 0],")
#print("\"x\":"    ,x_tv   + x_bv    + x_sv,",")
#print("\"y\":"    ,y_tv   + y_bv    + y_sv,",")
#print("\"z\":"    ,z_tv   + z_bv    + z_sv,",")
#print("\"dir_x\":",dx_tv  + dx_bv   + dx_sv,",")
#print("\"dir_y\":",dy_tv  + dy_bv  + dy_sv,",")
#print("\"dir_z\":",dz_tv  + dz_bv   + dz_sv,",")
#print("\"type\":",type_tv + type_bv + type_sv,",")
#print("}\n\n")

#print("//// Total number of PMTs : ",cnt_tv+cnt_sv+cnt_bv+cnt_t+cnt_s+cnt_b)


#
#
