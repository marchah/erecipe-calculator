[@react.component]
let make = (~preset: Constants.baseRatioPreset, ~handleSetBaseRatio) => {
  <div>
    <span> {ReasonReact.string("VG:")} </span>
    <input
      label="VG"
      type_="number"
      step=1.0
      value={Js.Int.toString(preset.vg)}
      onChange={event => {
        let value: int =
          int_of_float(
            Js.Math.trunc(
              ReactEvent.Form.target(event)##value >= 0
                ? ReactEvent.Form.target(event)##value : 0.0,
            ),
          );
        let newBaseRatio: Constants.baseRatioPreset = {
          vg: value > 100 ? 100 : value,
          pg: value > 100 ? 0 : 100 - value,
        };
        handleSetBaseRatio(_ => newBaseRatio);
      }}
    />
    <span> {ReasonReact.string("PG:")} </span>
    <input
      label="PG"
      type_="number"
      step=1.0
      value={Js.Int.toString(preset.pg)}
      onChange={event => {
        let value: int =
          int_of_float(
            Js.Math.trunc(
              ReactEvent.Form.target(event)##value >= 0
                ? ReactEvent.Form.target(event)##value : 0.0,
            ),
          );
        let newBaseRatio: Constants.baseRatioPreset = {
          vg: value > 100 ? 0 : 100 - value,
          pg: value > 100 ? 100 : value,
        };
        handleSetBaseRatio(_ => newBaseRatio);
      }}
    />
  </div>;
};