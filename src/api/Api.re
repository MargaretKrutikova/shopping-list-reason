[@bs.val] external apiBaseUrl: string = "process.env.REACT_APP_API_BASE_URL";

open Types;
open Decode;

let getShoppingList = (): Js.Promise.t(Belt.Result.t(shoppingList, unit)) =>
  Js.Promise.(
    Axios.get(apiBaseUrl)
    |> then_(response =>
         Belt.Result.Ok(response##data |> decodeShoppingList) |> resolve
       )
    |> catch(_ => Belt.Result.Error() |> resolve)
  );
