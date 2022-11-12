import jsonPlugin from '@rollup/plugin-json';
import typescriptPlugin from 'rollup-plugin-typescript2';
import babel from 'rollup-plugin-babel';
import resolve from '@rollup/plugin-node-resolve';
import { terser } from 'rollup-plugin-terser';
import replace from '@rollup/plugin-replace';
import commonjs from '@rollup/plugin-commonjs';
import modulePkg from "./package.json";

import { tmpdir } from 'os';
import { builtinModules } from 'module';
import path from 'path';

const coreModules = builtinModules.filter(name => !/(^_|\/)/.test(name));
const cacheRoot = path.join(tmpdir(), '.rpt2_cache');

export default async () => {

    return {
        input: "./src/index.ts",
        plugins: [
            babel(),
            resolve({
                extensions: [ ".ts", ".js" ]
            }),
            terser(),
            replace(),
            commonjs(),
            jsonPlugin(),
            typescriptPlugin({
                cacheRoot,
                useTsconfigDeclarationDir: false,
                tsconfigOverride: {
                    outDir: "lib",
                    rootDir: "src",
                    include: ["src"]
                }
            })
        ],
        external: [
            ...Object.keys(modulePkg.dependencies || {}),
            ...Object.keys(modulePkg.peerDependencies || {}),
            ...coreModules
        ],
        output: [
            {
                file: "lib/index.js",
                format: 'cjs',
                exports: 'named'
            },
            {
                file: "lib/index.mjs",
                format: 'esm'
            }
        ]
    }
}