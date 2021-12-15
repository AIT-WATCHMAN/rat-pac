{
name: "GEO",
index: "world",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "", // world volume has no mother
type: "box",
size: [20000.0, 20000.0, 20000.0], // mm, half-length
material: "air",
invisible: 1,
}

{
name: "GEO",
index: "pmt",
enable: 1,
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "world",
type: "pmtarray",
end_idx: 0, //idx of the last pmt
start_idx: 0, //idx of the first pmt
pmt_model: "r7081pe",
mu_metal: 0,
mu_metal_material: "aluminum",
mu_metal_surface: "aluminum",
light_cone: 0,
wls_plates: 1,
wls_hole_pos: [47.752,0.0],
wls_size: [191.77,146.304,6.35],
wls_inner_radius: 91.0,
wls_outer_radius: 115.0,
wls_offset: 50.0,
wls_material: "eljen_WLSP",
ref_surface: "aluminum",
ref_material: "aluminum",
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner",
efficiency_correction: 0.90000,
pos_table: "PMTINFO", //generated by positions.nb
orientation: "manual",
orient_point: [0.,0.,0.],
color: [0.3,0.5, 0.0, 0.2],
}

{
name: "GEO",
index: "rad_plane",
enable: 1,
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "world",
type: "box",

size: [191.77,1.0,146.304], // mm, half-length
//size: [350.0,1.0,350.0], // mm, half-length
position: [-47.752, -125.0, 0.0],
material: "air",
color: [0.1, 0.1, 0.8, 1.0],
invisible: 1,
}

