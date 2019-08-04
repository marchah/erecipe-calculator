[@react.component]
let make = () => {
  let (nicWeight, setNicWeight) = React.useState(() => 50.0);

  <div>
    <NicBaseSelector handleSetNicWeight=setNicWeight />
    <p> {ReasonReact.string(Js.Float.toString(nicWeight))} </p>
  </div>;
};