import module from "module";
import path from "path";

const requireNative = module.createRequire(import.meta.url);

export default requireNative(path.resolve(__dirname, "..", "build/Release/sandbox.node"));