# libhtml

HTML interface library in Cpp23

> [!IMPORTANT]
> Since this library is still in development, it may not work correctly or some
> functionalities might be missing

## Build

### Requirements

- [CMake](https://cmake.org/)

### Compilation

```bash
git clone https://github.com/AndreaGiorgino/libhtml
cd libhtml

./build.sh
```

Build targets:

- `build`
- `debug`
- `test`
- `example`

> Run `./build.sh --help` for the build script usage

## Usage

Look at [example](example) for an example usage

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
