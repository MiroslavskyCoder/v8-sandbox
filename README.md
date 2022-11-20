# @bymiroslavsky/v8-sandbox

# Installation

```sh
npm install --save @bymiroslavsky/v8-sandbox
```

## Examples

```js
import v8sandbox from '@bymiroslavsky/v8-sandbox';

const sandbox = new v8sandbox.Sandbox();

sandbox.setCode(`
  var g = test + 1;

  g;
`);
sandbox.setValue("test", 3);

console.log(sandbox.execute());

```