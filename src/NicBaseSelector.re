type nic = {
  concentration: int,
  base: Constants.base,
  index: int,
};

[@react.component]
let make = (~handleSetNicWeight) => {
  let nicOptions: list(nic) = [
    {concentration: 100, base: Constants.PG, index: 0},
    {concentration: 48, base: Constants.PG, index: 1},
    {concentration: 24, base: Constants.PG, index: 2},
    {concentration: 100, base: Constants.VG, index: 3},
    {concentration: 48, base: Constants.VG, index: 4},
    {concentration: 24, base: Constants.VG, index: 5},
  ];

  let (isCustomVisible, setCustomVisible) = React.useState(() => false);
  let (customNicValue, setCustomNicValue) = React.useState(() => 50);
  let (customNicBase, setCustomNicBase) = React.useState(() => Constants.PG);

  let handleSetNicWeight = (nic: int, base: Constants.base) => {
    let nicConcentration = Js.Int.toFloat(nic / 10);
    let nicWeight = nicConcentration *. Constants.nicWeightPerML;
    let tmp = 100.0 -. nicConcentration;

    let baseWeight =
      switch (base) {
      | PG => tmp *. Constants.pgWeightPerML
      | VG => tmp *. Constants.vgWeightPerML
      };

    let result = (nicWeight +. baseWeight) /. 100.0;

    handleSetNicWeight(_ => result);
  };

  let callHandleSetNicWeight = nicOption => {
    handleSetNicWeight(nicOption.concentration, nicOption.base);
  };

  let appendCustomOptionToList = list =>
    list
    @ [
      <option value="Custom" key="Cutom">
        {ReasonReact.string("Custom")}
      </option>,
    ];

  React.useEffect1(
    () => {
      let nicOption = List.hd(nicOptions);
      handleSetNicWeight(nicOption.concentration, nicOption.base);
      None;
    },
    [||],
  );

  <div>
    <select
      name="nic-selector"
      onChange={event =>
        (
          ReactEvent.Form.target(event)##value === "Custom"
            ? setCustomVisible(_ => true)
              |> (_ => handleSetNicWeight(customNicValue, customNicBase))
            : setCustomVisible(_ => false)
        )
        |> (
          _ =>
            ReactEvent.Form.target(event)##value !== "Custom"
              ? callHandleSetNicWeight(
                  List.nth(
                    nicOptions,
                    int_of_string(ReactEvent.Form.target(event)##value),
                  ),
                )
              : ()
        )
      }>
      {nicOptions
       |> List.map(item =>
            <option
              value={Js.Int.toString(item.index)}
              key={Js.Int.toString(item.index)}>
              {ReasonReact.string(
                 Js.Int.toString(item.concentration)
                 ++ "mg "
                 ++ Constants.convertBaseTypeToString(item.base),
               )}
            </option>
          )
       |> appendCustomOptionToList
       |> Array.of_list
       |> ReasonReact.array}
    </select>
    {isCustomVisible
       ? <div>
           <input
             type_="number"
             step=1.0
             value={Js.Int.toString(customNicValue)}
             onChange={event =>
               setCustomNicValue(ReactEvent.Form.target(event)##value)
               |> (
                 _ =>
                   handleSetNicWeight(
                     ReactEvent.Form.target(event)##value,
                     customNicBase,
                   )
               )
             }
           />
           <select
             name="nic-custom-selector"
             onChange={event =>
               setCustomNicBase(ReactEvent.Form.target(event)##value)
               |> (
                 _ =>
                   handleSetNicWeight(
                     customNicValue,
                     Constants.convertStringToBaseType(
                       ReactEvent.Form.target(event)##value,
                     ),
                   )
               )
             }>
             <option value="PG"> {ReasonReact.string("PG")} </option>
             <option value="VG"> {ReasonReact.string("VG")} </option>
           </select>
         </div>
       : ReasonReact.null}
  </div>;
};