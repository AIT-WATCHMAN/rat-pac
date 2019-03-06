{
name: "GEO",
index: "sourcecan",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "detector",
type: "tube",

material: "stainless_steel",
position: [0, 0, 0],
invisible: 0,
r_max: 100.0,
size_z: 300.0
}

{
name: "GEO",
index: "sourceair",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "sourcecan",
type: "tube",

material: "air",
position: [0, 0, 0],
invisible: 0,
r_max: 90.0,
size_z: 290.0
}
