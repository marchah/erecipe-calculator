[@react.component]
let make = (~initPresetNicBase: Constants.nicBasePreset, ~handleSetNicBase) => {
  let nicOptions: list(Constants.nicBasePreset) = [
    {concentration: 100, base: Constants.PG},
    {concentration: 48, base: Constants.PG},
    {concentration: 24, base: Constants.PG},
    {concentration: 100, base: Constants.VG},
    {concentration: 48, base: Constants.VG},
    {concentration: 24, base: Constants.VG},
  ];

  let (isCustomVisible, setCustomVisible) = React.useState(() => false);
  let (customNicValue, setCustomNicValue) = React.useState(() => 50);
  let (customNicBase, setCustomNicBase) = React.useState(() => Constants.PG);

  let appendCustomOptionToList = list =>
    list
    @ [
      <option value="Custom" key="Cutom"> {React.string("Custom")} </option>,
    ];

  let setCustomDefaultValue = (initValue: Constants.nicBasePreset) => {
    print_endline("No such item found!");
    setCustomVisible(_ => true);
    handleSetNicBase(initValue);
    setCustomNicValue(_ => initValue.concentration);
    setCustomNicBase(_ => initValue.base);
  };

  let rec findInitValueIndex = (list, index) =>
    switch (list) {
    | [] => List.length(nicOptions) // TODO: not working "Customs" not selected when use customs value as preset
    | [head, ..._] when head == initPresetNicBase => index
    | [_, ...tail] => findInitValueIndex(tail, index + 1)
    };

  let setInitPresetNicBase = list =>
    switch (
      List.find(
        (item: Constants.nicBasePreset) => item == initPresetNicBase,
        list,
      )
    ) {
    | exception Not_found => setCustomDefaultValue(initPresetNicBase)
    | item => handleSetNicBase(item)
    };

  React.useEffect0(() => {
    setInitPresetNicBase(nicOptions);

    None;
  });

  <div>
    <select
      name="nic-selector"
      defaultValue={Js.Int.toString(findInitValueIndex(nicOptions, 0))}
      onChange={event =>
        (
          ReactEvent.Form.target(event)##value === "Custom"
            ? setCustomVisible(_ => true)
              |> (
                _ => {
                  handleSetNicBase({
                    base: customNicBase,
                    concentration: customNicValue,
                  });
                }
              )
            : setCustomVisible(_ => false)
        )
        |> (
          _ =>
            ReactEvent.Form.target(event)##value !== "Custom"
              ? handleSetNicBase(
                  List.nth(
                    nicOptions,
                    int_of_string(ReactEvent.Form.target(event)##value),
                  ),
                )
              : ()
        )
      }>
      {nicOptions
       |> List.mapi((index, item: Constants.nicBasePreset) =>
            <option
              value={Js.Int.toString(index)} key={Js.Int.toString(index)}>
              {React.string(
                 Js.Int.toString(item.concentration)
                 ++ "mg "
                 ++ Constants.convertBaseTypeToString(item.base),
               )}
            </option>
          )
       |> appendCustomOptionToList
       |> Array.of_list
       |> React.array}
    </select>
    {isCustomVisible
       ? <div>
           <input
             type_="number"
             step=1.0
             value={Js.Int.toString(customNicValue)}
             onChange={event => {
               let nic = int_of_string(ReactEvent.Form.target(event)##value);
               setCustomNicValue(_ => nic);
               handleSetNicBase({base: customNicBase, concentration: nic});
             }}
           />
           <select
             name="nic-custom-selector"
             onChange={event => {
               let base =
                 Constants.convertStringToBaseType(
                   ReactEvent.Form.target(event)##value,
                 );
               setCustomNicBase(_ => base);
               handleSetNicBase({base, concentration: customNicValue});
             }}>
             <option value="PG"> {React.string("PG")} </option>
             <option value="VG"> {React.string("VG")} </option>
           </select>
         </div>
       : React.null}
  </div>;
};