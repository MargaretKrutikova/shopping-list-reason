[@bs.val] external apiBaseUrl: string = "process.env.REACT_APP_API_BASE_URL";

open Types;
open Decode;

let getCurrentListUrl = baseUrl => baseUrl ++ "/currentlist";
let publishShoppingListUrl = baseUrl => baseUrl ++ "/rpc/publish";

let getShoppingList = (): Js.Promise.t(shoppingList) =>
  Js.Promise.(
    Axios.get(getCurrentListUrl(apiBaseUrl))
    |> then_(response => response##data |> decodeShoppingList |> resolve)
  );

let updateShoppingList = (items: array(shoppingItem)) => {
  let requestBody = {
    "items":
      items
      |> Array.map(item =>
           {
             "product": item.product,
             "note": item.note,
             "assignee": item.assignee,
           }
         ),
  };

  Axios.postData(getCurrentListUrl(apiBaseUrl), requestBody)
  |> Js.Promise.then_(_ => () |> Js.Promise.resolve);
};

let publishShoppingList = () =>
  Axios.post(publishShoppingListUrl(apiBaseUrl))
  |> Js.Promise.then_(_ => () |> Js.Promise.resolve);
();
