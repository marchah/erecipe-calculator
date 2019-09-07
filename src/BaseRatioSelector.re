[@react.component]
let make = (~preference: Constants.baseRatioPreference, ~handleSetBaseRatio) => {
  <div>
    <span> {ReasonReact.string("VG:")} </span>
    <input
      label="VG"
      type_="number"
      step=1.0
      value={Js.Int.toString(preference.vg)}
      onChange={event => {
        Js.log(ReactEvent.Form.target(event)##value);
        let value: int =
          ReactEvent.Form.target(event)##value >= 0
            ? ReactEvent.Form.target(event)##value : 0;
        let newPreference: Constants.baseRatioPreference = {
          vg: value > 100 ? 100 : value,
          pg: value > 100 ? 0 : 100 - value,
        };
        handleSetBaseRatio(_ => newPreference);
      }}
    />
    <span> {ReasonReact.string("PG:")} </span>
    <input
      label="PG"
      type_="number"
      step=1.0
      value={Js.Int.toString(preference.pg)}
      onChange={event => {
        Js.log(ReactEvent.Form.target(event)##value);
        let value: int =
          ReactEvent.Form.target(event)##value >= 0
            ? ReactEvent.Form.target(event)##value : 0;
        let newPreference: Constants.baseRatioPreference = {
          vg: value > 100 ? 0 : 100 - value,
          pg: value > 100 ? 100 : value,
        };
        handleSetBaseRatio(_ => newPreference);
      }}
    />
  </div>;
};