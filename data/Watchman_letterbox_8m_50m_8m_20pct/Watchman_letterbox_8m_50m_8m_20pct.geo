{
name: "GEO",
index: "world",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "", // world volume has no mother
type: "box",
size: [11465.0, 32465.0, 11465.0], // mm, half-length
position: [0.0, 0.0, 0.0],
material: "air", //rock?
color: [0.85, 0.72, 1.0, 0.5],
invisible: 0,
}

///////////////////// Define the rock volumes. Thin slab of rock is assumed ////////////////////////

//Create a 1-m rock layer around a cylindrical cavern
{
name: "GEO",
index: "rock_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "world", // world volume has no mother
type: "box",
//size: [7000.0, 27000.0, 7000.0], // mm, half-length
size: [7000.0, 28000.0, 7000.0],
position: [0.0, 0.0, 1323.0], //this will allow for the concrete layer on the floor and not on the ceiling
material: "rock",
color: [0.43, 0.27, 0.13, 1.0],
invisible: 0,
//drawstyle: "solid"
}
//Create a 0.5m concrete layer on the walls and base
{
name: "GEO",
index: "rock_2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "rock_1",
type: "box",
//size: [5500.0, 26500.0, 5500.0], // mm, half-length
size: [5100.0, 26100.0, 5100.0], 
position: [0.0, 0.0, 0.0], // this will give a concrete layer on the floor and not on the ceiling
material: "rock", // changed from "gunite" (L. Kneale)
color: [0.43, 0.27, 0.13, 1.0],
invisible: 0,
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
type: "box",
//size: [5000.0, 26000.0, 5000.0], // mm, half-length
size: [5000.0, 26000.0, 5000.0], 
position: [0.0, 0.0, 0.0],
material: "air",
invisible: 0,
color: [0.85, 0.72, 1.0, 0.5],
}
{
name: "GEO",
index: "ibeam",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "cavern_1",
type: "box",
//size: [4500.0, 24500.0, 4500.0], // mm, half-length
size: [4527.0, 25527.0, 4527.0], 
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
type: "box",
//size: [5000.0, 26000.0, 5000.0], // mm, half-length
size: [4500.0, 25500.0, 4500.0], 
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
type: "box",
//size: [4500.0, 24500.0, 4500.0], // mm, half-length
size: [3650.0, 24650.0, 3850.0], 
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
type: "box",
//size: [4498.125, 24498.125, 4498.125], // mm, half-length
size: [3600.0, 24600.0, 3800.0],
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
type: "box",
//size: [4498.125, 24498.125, 4498.125], // mm, half-length
size: [3456.0, 24456.0, 3456.0],
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
type: "box",
//size: [4498.125, 24498.125, 4498.125], // mm, half-length
size: [3450.0, 24450.0, 3450.0],
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
type: "box",
//size: [3508.125, 23508.125, 3508.125], // mm, half-length
size: [3070.0,24070.0,3070.0],
position: [0.0, 0.0, 0.0],
material: "polypropylene",
color: [0.,0.,0.,1.0],
drawstyle: "solid",
}
{
name: "GEO",
index: "detector_target_gb", // gb: gamma buffer
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "black_sheet",
type: "box",
//size: [3498.125, 23498.125, 3498.125] // mm, half-length
size: [3065.0,24065.0,3065.0],
position: [0.0, 0.0, 0.0],
material: "doped_water",
color: [0.2,0.2,0.9,0.2],
drawstyle: "solid"
}
{
name: "GEO",
index: "detector_target_fv",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector_target_gb",
type: "box",
//size: [3498.125, 23498.125, 3498.125] // mm, half-length
size: [2915.0,23915.0,2915.0],
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
end_idx: 4943, //idx of the last pmt
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
