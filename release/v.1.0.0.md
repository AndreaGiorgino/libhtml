# libhtml v1.0.0

## Release notes

- html document decoding/encoding
- html nodes decoding/encoding
- DOM manipulation interface for properties and children

## ABI quick reference

### HtmlDoc

Capacity:

| Method name | Brief                       |
| :---------- | :-------------------------- |
| `propsSize` | Get the properties map size |

Lookup:

| Method name | Brief                  |
| :---------- | :--------------------- |
| `prop`      | Get the property value |
| `props`     | Get the properties map |
| `head`      | Get the document head  |
| `body`      | Get the document body  |

Modifiers:

| Method name  | Brief                                |
| :----------- | :----------------------------------- |
| `prop`       | Set a property value and return self |
| `clearProps` | Clear the properties map             |
| `head`       | Set the document head                |
| `body`       | Set the document body                |

IO interface:

| Method name | Brief                                      |
| :---------- | :----------------------------------------- |
| `decode`    | Decode an html document from stream/string |
| `encode`    | Encode the document                        |

### HtmlNode

Capacity:

| Method name    | Brief                            |
| :------------- | :------------------------------- |
| `propsSize`    | Get the properties map size      |
| `childrenSize` | Get the children collection size |

Lookup:

| Method name | Brief                       |
| :---------- | :-------------------------- |
| `tagName`   | Get the tag name            |
| `prop`      | Get the property value      |
| `props`     | Get the properties map      |
| `child`     | Get the child node at index |
| `children`  | Get the children collection |

Modifiers:

| Method name     | Brief                                |
| :-------------- | :----------------------------------- |
| `tagName`       | Set the tag name                     |
| `prop`          | Set a property value and return self |
| `clearProps`    | Clear the properties map             |
| `addChild`      | Add a child node and return self     |
| `clearChildren` | Clear the children collection        |

IO interface:

| Method name | Brief                                  |
| :---------- | :------------------------------------- |
| `decode`    | Decode an html node from stream/string |
| `encode`    | Encode the node                        |

### Exceptions

| Exception name | brief                       |
| :------------- | :-------------------------- |
| `ParseError`   | Represents a parsing error  |
| `DocError`     | Represents a document error |
