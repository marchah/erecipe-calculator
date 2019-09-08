[@react.component]
let make = () => {
  let (nicWeight, setNicWeight) = React.useState(() => 50.0);

  let preset: Constants.preset = {
    name: "default",
    baseRatio: {
      vg: 70,
      pg: 30,
    },
    size: 100,
  };

  let (baseRatio, setBaseRatio) = React.useState(() => preset.baseRatio);
  let (size, setSize) = React.useState(() => preset.size);

  <div>
    <div>
      <NicBaseSelector handleSetNicWeight=setNicWeight />
      <p> {ReasonReact.string(Js.Float.toString(nicWeight))} </p>
    </div>
    <div>
      <BaseRatioSelector preset=baseRatio handleSetBaseRatio=setBaseRatio />
    </div>
    <div> <SizeSelector size handleSetSize=setSize /> </div>
  </div>;
};