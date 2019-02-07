[@bs.val] external apiBaseUrl: string = "process.env.REACT_APP_API_BASE_URL";

open Types;
open Decode;

type apiShoppingListResponse =
  | Success(shoppingList)
  | Error;

let getShoppingList = (): Js.Promise.t(apiShoppingListResponse) =>
  Js.Promise.(
    Axios.get(apiBaseUrl)
    |> then_(response =>
         Success(response##data |> decodeShoppingList) |> resolve
       )
    |> catch(_ => Error |> resolve)
  );
