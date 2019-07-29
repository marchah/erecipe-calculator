type nic = {
  value: float,
  label: string,
};

[@react.component]
let make = () => {
  let nicOptions: list(nic) = [
    {value: 1.035, label: "100mg PG"},
    {value: 1.036656, label: "48mg PG"},
    {value: 1.037328, label: "24mg PG"},
    {value: 1.235, label: "100mg VG"},
    {value: 1.248, label: "48mg VG"},
    {value: 1.254, label: "24mg VG"},
    {value: 0.0, label: "Custom"},
  ];

  let (isCustomVisible, setCustomVisible) = React.useState(() => false);
  let (nicWeight, setNicWeight) = React.useState(() => 0);

  let handleSetNicWeight = value => {
    JS.log("OKKKK");
    JS.log(value);
  };

  <div>
    <select
      name="nic-selector"
      onChange={event =>
        ReactEvent.Form.target(event)##value === "Custom"
          ? setCustomVisible(_ => true)
          : setCustomVisible(_ => false) && handleSetNicWeight(event)
      }>
      {nicOptions
       |> List.map(item =>
            <option value={item.label} key={item.label}>
              {ReasonReact.string(item.label)}
            </option>
          )
       |> Array.of_list
       |> ReasonReact.array}
    </select>
    {isCustomVisible
       ? <div>
           <input type_="number" step=1.0 />
           <select>
             <option value="PG"> {ReasonReact.string("PG")} </option>
             <option value="VG"> {ReasonReact.string("VG")} </option>
           </select>
         </div>
       : [] |> Array.of_list |> ReasonReact.array}
  </div>; /* need a better way */
};