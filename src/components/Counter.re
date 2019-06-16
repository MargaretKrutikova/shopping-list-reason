open Redux;

[@react.component]
let make = () => {
  let counter = useSelector(state => state.count);
  let dispatch = useDispatch();

  <div>
    <button onClick={_ => dispatch(Increment)}>
      {ReasonReact.string("Increment")}
    </button>
    <span> {string_of_int(counter) |> ReasonReact.string} </span>
    <button onClick={_ => dispatch(Decrement)}>
      {ReasonReact.string("Decrement")}
    </button>
  </div>;
};
