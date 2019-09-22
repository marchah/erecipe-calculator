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

  let rec findInitValueIndex = (list, index) =>
    switch (List.hd(list) == initPresetNicBase) {
    | true => index
    | _ => findInitValueIndex(List.tl(list), index + 1)
    };

  React.useEffect0(() => {
    switch (
      List.find(
        (item: Constants.nicBasePreset) => item == initPresetNicBase,
        nicOptions,
      )
    ) {
    | exception Not_found => print_endline("Not found!")
    | item => handleSetNicBase(item)
    };

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