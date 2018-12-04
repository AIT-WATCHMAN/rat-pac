{
name: "GEO",
index: "world",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "", // world volume has no mother
type: "box",
size: [20000.0, 20000.0, 20000.0], // mm, half-length
material: "air", //rock?
invisible: 1,
}

///////////////////// Define the rock volumes. Thin slab of rock is assumed ////////////////////////

//Create a 1-m rock layer around a cylindrical cavern
{
name: "GEO",
index: "rock_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "world", // world volume has no mother
type: "tube",
r_max: 14000.00, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: 13750.00,
position: [0.0, 0.0, 0.0], //this will allow for the concrete layer on the floor and not on the ceiling
material: "rock",
invisible: 1,
}


//Create a 0.5m concrete layer on the walls and base
{
name: "GEO",
index: "concrete", // changed from "gunite" for updated design (L. Kneale)
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "rock_1",
type: "tube",
r_max: 13000.0, // changed to incorporate 0.5m layer of concrete on walls (L.Kneale) (cavern size is 25m i.e. 12.5m radius)
size_z: 12751.0, // the extraneous mm ensures that the cavern volume is enclosed by the "concrete" mother volume
position: [0.0, 0.0, -250.0], // this will give a concrete layer on the floor and not on the ceiling
material: "concrete", // changed from "gunite" (L. Kneale)
invisible: 1,
}


//Create the cavern space between the tank and concrete
{
name: "GEO",
index: "cavern",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "concrete",
type: "tube",
r_max: 12500.0,
size_z: 12500.0,
position: [0.0, 0.0, 250.0],
material: "air",
invisible: 1,
}

////////////////////////////////// Define the rock volumes done.///////////////////////////////////


////////////////////////////////// Define detector properties.  ///////////////////////////////////

{
name: "GEO",
index: "tank",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "cavern",
type: "tube",
r_max: 8000.0,
size_z: 8000.0,
position: [0.0, 0.0, 0.0],
material: "stainless_steel",
color: [0.2,0.2,0.2,0.1],
drawstyle: "solid"
}

{
name: "GEO",
index: "detector",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "tank",
type: "tube",
r_max: 7984.125,
size_z: 7984.125, //half height, mm
position: [0.0, 0.0, 0.0],
material: "doped_water",
color: [0.2,0.2,0.2,0.1],
drawstyle: "solid"
}

{ //position table for hold-up cables
name: "cable_pos",
valid_begin: [0, 0],
valid_end: [0, 0],
x: [6406.35d,6392.63d,6351.54d,6283.25d,6188.06d,6066.37d,5918.7d,5745.68d,5548.06d,5326.69d,5082.5d,4816.55d,4529.97d,4224.d,3899.94d,3559.18d,3203.18d,2833.46d,2451.6d,2059.25d,1658.09d,1249.82d,836.196d,418.995d,0.d,-418.995d,-836.196d,-1249.82d,-1658.09d,-2059.25d,-2451.6d,-2833.46d,-3203.18d,-3559.18d,-3899.94d,-4224.d,-4529.97d,-4816.55d,-5082.5d,-5326.69d,-5548.06d,-5745.68d,-5918.7d,-6066.37d,-6188.06d,-6283.25d,-6351.54d,-6392.63d,-6406.35d,-6392.63d,-6351.54d,-6283.25d,-6188.06d,-6066.37d,-5918.7d,-5745.68d,-5548.06d,-5326.69d,-5082.5d,-4816.55d,-4529.97d,-4224.d,-3899.94d,-3559.18d,-3203.18d,-2833.46d,-2451.6d,-2059.25d,-1658.09d,-1249.82d,-836.196d,-418.995d,0.d,418.995d,836.196d,1249.82d,1658.09d,2059.25d,2451.6d,2833.46d,3203.18d,3559.18d,3899.94d,4224.d,4529.97d,4816.55d,5082.5d,5326.69d,5548.06d,5745.68d,5918.7d,6066.37d,6188.06d,6283.25d,6351.54d,6392.63d,],
y: [0.d,418.995d,836.196d,1249.82d,1658.09d,2059.25d,2451.6d,2833.46d,3203.18d,3559.18d,3899.94d,4224.d,4529.97d,4816.55d,5082.5d,5326.69d,5548.06d,5745.68d,5918.7d,6066.37d,6188.06d,6283.25d,6351.54d,6392.63d,6406.35d,6392.63d,6351.54d,6283.25d,6188.06d,6066.37d,5918.7d,5745.68d,5548.06d,5326.69d,5082.5d,4816.55d,4529.97d,4224.d,3899.94d,3559.18d,3203.18d,2833.46d,2451.6d,2059.25d,1658.09d,1249.82d,836.196d,418.995d,0.d,-418.995d,-836.196d,-1249.82d,-1658.09d,-2059.25d,-2451.6d,-2833.46d,-3203.18d,-3559.18d,-3899.94d,-4224.d,-4529.97d,-4816.55d,-5082.5d,-5326.69d,-5548.06d,-5745.68d,-5918.7d,-6066.37d,-6188.06d,-6283.25d,-6351.54d,-6392.63d,-6406.35d,-6392.63d,-6351.54d,-6283.25d,-6188.06d,-6066.37d,-5918.7d,-5745.68d,-5548.06d,-5326.69d,-5082.5d,-4816.55d,-4529.97d,-4224.d,-3899.94d,-3559.18d,-3203.18d,-2833.46d,-2451.6d,-2059.25d,-1658.09d,-1249.82d,-836.196d,-418.995d,],
z: [0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,],
dir_x: [0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,],
dir_y: [0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,0.d,],
dir_z: [1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,1.d,],
}

{
name: "GEO",
index: "cables",
enable: 1,
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tubearray",
r_max: 9.525,
size_z: 7984.125,
pos_table: "cable_pos",
orientation: "manual",
material: "stainless_steel",
drawstyle: "solid",
color: [0.2,0.2,0.2,0.1],
}

{
name: "inner_vis",
valid_begin: [0, 0],
valid_end: [0, 0],
color: [0.0,0.5, 0.0, 0.2],
}

{
name: "veto_vis",
valid_begin: [0, 0],
valid_end: [0, 0],
color: [1.0, 0.0, 1.0, 0.3],
}

{
name: "GEO",
index: "shield",
enable: 1,
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "watchmanshield", //see the geo factory

//builds pmt backs/covers
pmtinfo_table: "PMTINFO",
back_semi_x: 152.5,
back_semi_y: 152.5,
back_semi_z: 301.5, //this should perhaps be a little larger
back_thickness: 3.175,
back_material: "polypropylene",
orientation_inner: "manual", //should match "inner_pmts" orientation
orient_point_inner: [0.,0.,0.], //only used if orientation_inner is "point"
inner_start: 0,
inner_len: 4330, //set to 0 to prevent building covers
inner_back_surface: "black_water",
inner_back_vis: "inner_vis",
orientation_veto: "manual", //should match "veto_pmts" orientation
orient_point_veto: [0.,0.,0.], //only used if orientation_veto is "point"
veto_start: 4330,
veto_len: 482, //set to 0 to prevent building covers
veto_back_surface: "black_water",
veto_back_vis: "veto_vis",

//properties to define the shield
detector_size_z: 16000.0,//Full Height
detector_size_d: 16000.0,//Full Diameter
veto_thickness_r: 1600.0,
veto_thickness_z: 1600.0,
steel_thickness: 1.5875,
cols: 96,
rows: 30,
frame_material: "stainless_steel",
inside_surface: "black_water",
outside_surface: "white_water",

drawstyle: "solid",
position: [0.0, 0.0, 0.0],
color: [0.1, 0.8, 0.1, 0.01],
}

/* Will not work with WATCHMAKERS as it is now
// Fiducial defined as separate geometry component a la baccarat
{
name: "GEO",
index: "fiducial",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
r_max: 5420.0,
size_z: 5420.0,
position: [0.0, 0.0, 0.0],
material: "doped_water",
color: [0.2,0.2,0.2,0.1],
drawstyle: "solid",
invisible: 1
}*/

{
name: "GEO",
index: "inner_pmts",
enable: 1,
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "pmtarray",
end_idx: 4329, //idx of the last pmt
start_idx: 0, //idx of the first pmt
pmt_model: "r7081pe",
mu_metal: 0,
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner",
efficiency_correction: 0.90000,
pos_table: "PMTINFO", //generated by positions.nb
orientation: "manual",
orient_point: [0.,0.,0.],
color: [0.3,0.5, 0.0, 0.7],
}

{
name: "GEO",
index: "veto_pmts",
enable: 1,
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "pmtarray",
end_idx: 4811, //idx of the last pmt
start_idx: 4330, //idx of the first pmt
pmt_model: "r7081pe",
mu_metal: 0,
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/veto",
efficiency_correction: 0.90000,
pos_table: "PMTINFO", //generated by positions.nb
orientation: "manual",
orient_point: [0.,0.,0.],
}
