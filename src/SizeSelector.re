[@react.component]
let make = (~size: int, ~handleSetSize) => {
  <div>
    <span> {ReasonReact.string("Size:")} </span>
    <input
      label="size"
      type_="number"
      step=1.0
      value={Js.Int.toString(size)}
      onChange={event => {
        let newSize: int =
          int_of_float(Js.Math.trunc(ReactEvent.Form.target(event)##value));
        handleSetSize(_ => newSize);
      }}
    />
  </div>;
};