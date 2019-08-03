/* TODO: create constants file */
let nicWeightPerML = 1.01;
let pgWeightPerML = 1.038;
let vgWeightPerML = 1.26;

type base =
  | PG
  | VG;

type nic = {
  concentration: int,
  base,
};

/*
 {value: 1.035, label: "100mg PG"},
     {value: 1.036656, label: "48mg PG"},
     {value: 1.037328, label: "24mg PG"},
     {value: 1.235, label: "100mg VG"},
     {value: 1.248, label: "48mg VG"},
     {value: 1.254, label: "24mg VG"},
     {value: 0.0, label: "Custom"},
 */

[@react.component]
let make = () => {
  let nicOptions: list(nic) = [
    {concentration: 100, base: PG},
    {concentration: 48, base: PG},
    {concentration: 24, base: PG},
    {concentration: 100, base: VG},
    {concentration: 48, base: VG},
    {concentration: 24, base: VG},
  ];
  /*
     let (isCustomVisible, setCustomVisible) = React.useState(() => false);
     let (nicWeight, setNicWeight) =
       React.useState(() => List.hd(nicOptions).value);
     let (customNicValue, setCustomNicValue) = React.useState(() => 50.0);
     let (customNicBase, setCustomNicBase) = React.useState(() => "PG");

     let handleSetNicWeight = (value: float) => {
       Js.log("handleSetNicWeight");
       Js.log(value);
       setNicWeight(_ => value);
     };

     let handleCustomNicSelection = () => {
       Js.log("handleCustomNicSelection");
       Js.log(customNicValue);
       let nic = customNicValue /. 10.0 *. nicWeightPerML;
       let tmp = 100.0 -. nic;

       let base =
         customNicBase === "PG" ? tmp *. pgWeightPerML : tmp *. vgWeightPerML;

       Js.log(base +. nic);
     };
   */
  <div>
    <select name="nic-selector">
      /* onChange={event =>
           ReactEvent.Form.target(event)##value == "0"
             ? setCustomVisible(_ => true)
             : setCustomVisible(_ => false)
               |> (
                 _ => handleSetNicWeight(ReactEvent.Form.target(event)##value)
               )
         }*/

        {nicOptions
         |> List.map(item =>
              <option
                value={Js.Float.toString(item.value)}
                key={
                  Js.Int.toString(item.concentration))
                  ++ item.base
                }>
                {ReasonReact.string(item.concentration)
                 ++ ReasonReact.string(item.base)}
              </option>
            )
         |> Array.of_list
         |> ReasonReact.array}
      </select>
  </div>;
  /* {isCustomVisible
     ? <div>
         <input
           type_="number"
           step=1.0
           value={Js.Float.toString(customNicValue)}
           onChange={event =>
             setCustomNicValue(ReactEvent.Form.target(event)##value)
           }
         />
         <select
           name="nic-custom-selector"
           onChange={event =>
             setCustomNicBase(ReactEvent.Form.target(event)##value)
           }>
           <option value="PG"> {ReasonReact.string("PG")} </option>
           <option value="VG"> {ReasonReact.string("VG")} </option>
         </select>
       </div>
     : ReasonReact.null} */
};