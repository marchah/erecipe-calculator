[@react.component]
let make = () => {
  let (nicWeight, setNicWeight) = React.useState(() => 50.0);

  let preference: Constants.preference = {
    baseRatio: {
      vg: 70,
      pg: 30,
    },
  };

  let (baseRatio, setBaseRatio) = React.useState(() => preference.baseRatio);

  <div>
    <div>
      <NicBaseSelector handleSetNicWeight=setNicWeight />
      <p> {ReasonReact.string(Js.Float.toString(nicWeight))} </p>
    </div>
    <div>
      <BaseRatioSelector
        preference=baseRatio
        handleSetBaseRatio=setBaseRatio
      />
    </div>
  </div>;
};