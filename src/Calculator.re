[@react.component]
let make = () => {
  let (nicWeight, setNicWeight) = React.useState(() => 50.0);

  let preset: Constants.preset = {
    name: "default",
    nicBase: {
      base: Constants.PG,
      concentration: 99,
    },
    baseRatio: {
      vg: 70,
      pg: 30,
    },
    size: 100,
  };

  let (nicBase, setNicBase) = React.useState(() => preset.nicBase);
  let (baseRatio, setBaseRatio) = React.useState(() => preset.baseRatio);
  let (size, setSize) = React.useState(() => preset.size);

  let handleSetNicBase = newNicBase => {
    setNicBase(_ => newNicBase);
    let nicConcentration = Js.Int.toFloat(newNicBase.concentration) /. 10.0;
    let nicWeight = nicConcentration *. Constants.nicWeightPerML;
    let tmp = 100.0 -. nicConcentration;

    let baseWeight =
      switch (newNicBase.base) {
      | PG => tmp *. Constants.pgWeightPerML
      | VG => tmp *. Constants.vgWeightPerML
      };

    let result = (nicWeight +. baseWeight) /. 100.0;

    setNicWeight(_ => result);
  };

  <div>
    <div>
      <NicBaseSelector initPresetNicBase=nicBase handleSetNicBase />
      <p> {ReasonReact.string(Js.Float.toString(nicWeight))} </p>
    </div>
    <div>
      <BaseRatioSelector preset=baseRatio handleSetBaseRatio=setBaseRatio />
    </div>
    <div> <SizeSelector size handleSetSize=setSize /> </div>
  </div>;
};