open Redux;

[@react.component]
let make = () => {
  let counter = App.Store.useSelector(state => state.count);
  let dispatch = App.Store.useDispatch();

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
