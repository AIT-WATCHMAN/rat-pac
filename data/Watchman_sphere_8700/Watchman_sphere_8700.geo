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
//color: [1.0,0.6,0.0,1.0],
//drawstyle: "solid"
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
//color: [0.8,0.8,0.8,0.8],
//drawstyle: "solid"
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
r_max: 10000.0,
size_z: 10000.0,
position: [0.0, 0.0, 0.0],
material: "stainless_steel",
color: [0.6,0.6,0.9,0.01],
drawstyle: "solid"
}

{
name: "GEO",
index: "detector",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "tank",
type: "tube",
r_max: 9984.125,
size_z: 9984.125, //half height, mm
position: [0.0, 0.0, 0.0],
material: "doped_water",
color: [0.2,0.2,0.9,0.2],
drawstyle: "solid"
}


/*
//reflective tarp for veto region - including reflection properties
{
name: "GEO",
index: "white_sheet",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "sphere",
r_max:  6700.0,// These are guessed. Need a proper estimate
position: [0.0, 0.0, 0.0],
material: "polypropylene",
color: [0.9,0.9,0.9,0.3],
drawstyle: "solid",
}
{
//Bergevin: Set the interface were reflection can occur. Must make sure volume1 and volume2
//are in the correct order
name: "GEO",
index: "midsurface_white_sheet",
valid_begin: [0, 0],
valid_end: [0, 0],
invisible: 0, // omitted for visualization
mother: "white_sheet", //not used but needs to be a valid name, parent of 'a' and 'b' would be best choice
type: "border",
volume1: "detector",
volume2: "white_sheet",
reverse: 1, //0 only considers photons from a->b, 1 does both directions
surface: "reflective_tarp",
}
*/




//reflective tarp for veto region - including reflection properties
{
name: "GEO",
index: "white_sheet_tank_side",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
r_max:  9970.0,// These are guessed. Need a proper estimate
r_min:  9960.0,//
size_z: 9970.0,// These are guessed. Need a proper estimate
position: [0.0, 0.0, 0.0],
material: "polypropylene",
color: [0.9,0.9,0.2,0.1],
drawstyle: "solid",
}
{
//Bergevin: Set the interface were reflection can occur. Must make sure volume1 and volume2
//are in the correct order
name: "GEO",
index: "midsurface_white_sheet_tank_side",
valid_begin: [0, 0],
valid_end: [0, 0],
invisible: 0, // omitted for visualization
mother: "white_sheet_tank_side", //not used but needs to be a valid name, parent of 'a' and 'b' would be best choice
type: "border",
volume1: "detector",
volume2: "white_sheet_tank_side",
reverse: 1, //0 only considers photons from a->b, 1 does both directions
surface: "reflective_tarp",
}
{name: "GEO",
index: "white_sheet_tank_top",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
r_max:  9965.0,// These are guessed. Need a proper estimate
size_z: 10.0,// These are guessed. Need a proper estimate
position: [0.0, 0.0, 9970.0],
material: "polypropylene",
color: [0.9,0.9,0.2,0.1],
drawstyle: "solid",
}
{
//Bergevin: Set the interface were reflection can occur. Must make sure volume1 and volume2
//are in the correct order
name: "GEO",
index: "midsurface_white_sheet_tank_top",
valid_begin: [0, 0],
valid_end: [0, 0],
invisible: 0, // omitted for visualization
mother: "white_sheet_tank_top", //not used but needs to be a valid name, parent of 'a' and 'b' would be best choice
type: "border",
volume1: "detector",
volume2: "white_sheet_tank_top",
reverse: 1, //0 only considers photons from a->b, 1 does both directions
surface: "reflective_tarp",
}
{
name: "GEO",
index: "white_sheet_tank_bottom",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",
r_max:  9965.0,// These are guessed. Need a proper estimate
size_z: 10.0,// These are guessed. Need a proper estimate
position: [0.0, 0.0, -9970.0],
material: "polypropylene",
color: [0.9,0.9,0.2,0.1],
drawstyle: "solid",
}
{
//Bergevin: Set the interface were reflection can occur. Must make sure volume1 and volume2
//are in the correct order
name: "GEO",
index: "midsurface_white_sheet_tank_bottom",
valid_begin: [0, 0],
valid_end: [0, 0],
invisible: 0, // omitted for visualization
mother: "white_sheet_tank_bottom", //not used but needs to be a valid name, parent of 'a' and 'b' would be best choice
type: "border",
volume1: "detector",
volume2: "white_sheet_tank_bottom",
reverse: 1, //0 only considers photons from a->b, 1 does both directions
surface: "reflective_tarp",
}

//non-reflective tarp for inner detector - including non-reflective properties
{
name: "GEO",
index: "black_sheet_side",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "sphere",
r_max:  8705.0,// tarp will be 5 mm thick
position: [0.0, 0.0, 0.0],
material: "polypropylene",
color: [0.,0.,0.,1.0],
drawstyle: "solid",
}

{
name: "GEO",
index: "inner_detector",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "tank",
type: "sphere",
r_max: 8700.0,
position: [0.0, 0.0, 0.0],
material: "doped_water",
color: [0.2,0.2,0.9,0.2],
drawstyle: "solid"
}


{
//Bergevin: Set the interface were reflection can occur. Must make sure volume1 and volume2
//are in the correct order
name: "GEO",
index: "midsurface_black_sheet_side",
valid_begin: [0, 0],
valid_end: [0, 0],
invisible: 0, // omitted for visualization
mother: "black_sheet_side", //not used but needs to be a valid name, parent of 'a' and 'b' would be best choice
type: "border",
volume1: "inner_detector",
volume2: "black_sheet_side",
reverse: 1, //0 only considers photons from a->b, 1 does both directions
surface: "nonreflective_tarp",
}






{
name: "inner_vis",
valid_begin: [0, 0],
valid_end: [0, 0],
color: [0.0,0.5, 0.0, 0.2],
}


{
name: "GEO",
index: "inner_pmts",
enable: 1,
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "pmtarray",
end_idx: 3844,  //idx of the last pmt
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
orientation: "point",
orient_point: [0.,0.,0.],
color: [0.3,0.5, 0.0, 0.2],
}
