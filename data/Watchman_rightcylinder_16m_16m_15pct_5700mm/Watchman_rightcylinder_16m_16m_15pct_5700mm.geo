{
name: "GEO",
index: "world",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "", // world volume has no mother
type: "tube",
r_max: 18500.0, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: 18500.0,
position: [0.0, 0.0, 0.0],
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
r_max: 11400.0, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: 11400.0,
position: [0.0, 0.0, 1323.0], //this will allow for the concrete layer on the floor and not on the ceiling
material: "rock",
invisible: 1,
//color: [1.0,0.6,0.0,1.0],
//drawstyle: "solid"
}


//Create a 0.5m concrete layer on the walls and base
{
name: "GEO",
index: "rock_2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "rock_1",
type: "tube",
r_max: 9500.0, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: 9500.0,
position: [0.0, 0.0, 0.0], // this will give a concrete layer on the floor and not on the ceiling
material: "rock", // changed from "gunite" (L. Kneale)
invisible: 1,
//color: [0.8,0.8,0.8,0.8],
//drawstyle: "solid"
}
//Create the cavern space between the tank and concrete
{
name: "GEO",
index: "cavern_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "rock_2",
type: "tube",
r_max: 9400.0, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: 9400.0,
position: [0.0, 0.0, 0.0],
material: "air",
invisible: 1,
}
{name:"GEO",
index: "ibeam",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "cavern_1",
type: "tube",
r_max: 8927.0,
size_z: 8927.0,
position: [0.0, 0.0,-473.0],
material: "stainless_steel",
color: [0.96,0.95,0.27,1.0],
drawstyle: "solid"
}
{
name: "GEO",
index: "cavern_2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "ibeam",
type: "tube",
r_max: 8900.0,
size_z: 8900.0, 
position: [0.0, 0.0, 0.0],
material: "air",
color: [0.85, 0.72, 1.0, 0.5],
invisible: 0,
}
////////////////////////////////// Define the rock volumes done.///////////////////////////////////
{
name: "GEO",
index: "tank",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "cavern_2",
type: "tube",
r_max: 8050.0, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: 8050.0,
position: [0.0, 0.0, -650.0],
material: "stainless_steel",
color: [0.43,0.70,0.90,1.0],
drawstyle: "solid"
}
{
name: "GEO",
index: "detector_veto1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "tank",
type: "tube",
r_max: 8000.0, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: 8000.0,
position: [0.0, 0.0, 0.0],
material: "doped_water",
color: [0.2,0.2,0.9,0.2],
drawstyle: "solid"
}
{
name: "GEO",
index: "psup",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector_veto1",
type: "tube",
r_max: 6091.0, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: 6091.0,
position: [0.0, 0.0, -200.0],
material: "stainless_steel",
color: [0.0,0.5,0.18,1.0],
drawstyle: "solid"
}
{
name: "GEO",
index: "detector_veto2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "psup",
type: "tube",
r_max: 6085.0, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: 6085.0,
position: [0.0, 0.0, 0.0],
material: "doped_water",
color: [0.2,0.2,0.9,0.2],
drawstyle: "solid"
}
{
name: "GEO",
index: "black_sheet",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector_veto2",
type: "tube",
r_max: 5705.0, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: 5705.0,
position: [0.0, 0.0, 0.0],
material: "polypropylene",
color: [0.,0.,0.,1.0],
drawstyle: "solid",
}
{
name: "GEO",
index: "detector_target_gb",// gb: gamma buffer
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "black_sheet",
type: "tube",
r_max: 5700.0, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: 5700.0,
position: [0.0, 0.0, 0.0],
material: "doped_water",
color: [0.2,0.2,0.9,0.2],
drawstyle: "solid"
}
{
name: "GEO",
index: "detector_target_fv", // fv : fiducial volume
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector_target_gb", // gb : gamma buffer
type: "tube",
r_max: 5550.0, // changed to accommodate 0.5m-thick layer of concrete on walls (L. Kneale)
size_z: 5550.0,
position: [0.0, 0.0, 0.0],
material: "doped_water",
color: [0.2,0.2,0.9,0.2],
drawstyle: "solid"
}
{
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
}

{
name: "GEO",
index: "inner_pmts",
enable: 1,
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector_target_gb",
type: "pmtarray",
end_idx: 1823, //idx of the last pmt
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
}
