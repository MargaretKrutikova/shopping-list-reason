type assignee = {
  id: int,
  name: string,
};

type shoppingItem = {
  product: string,
  note: string,
  assignee: option(assignee),
};

type shoppingList = {
  name: string,
  status: string,
  items: array(shoppingItem),
};
