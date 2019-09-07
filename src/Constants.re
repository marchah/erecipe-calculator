let nicWeightPerML = 1.01;
let pgWeightPerML = 1.038;
let vgWeightPerML = 1.26;

type base =
  | PG
  | VG;

let convertBaseTypeToString = (value: base): string =>
  value === PG ? "PG" : "VG";
let convertStringToBaseType = (str: string): base => str === "PG" ? PG : VG;

type baseRatioPreset = {
  vg: int,
  pg: int,
};

type preset = {
  name: string,
  baseRatio: baseRatioPreset,
};