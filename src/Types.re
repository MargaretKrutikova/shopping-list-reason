type assignee = {name: string};

type shoppingItem = {
  product: string,
  note: string,
  assignee: option(string),
  isPurchased: bool,
};

type listStatus =
  | Editing
  | Shopping
  | Completed;

type shoppingList = {
  name: string,
  status: listStatus,
  items: array(shoppingItem),
};

exception UnhandledPromise;
