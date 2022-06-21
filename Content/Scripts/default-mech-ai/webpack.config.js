const path = require('path');
const NodePolyfillPlugin = require("node-polyfill-webpack-plugin")
module.exports = {
    mode: "development",
    devtool: "source-map",
    entry: {
        main: "./src/mech.ts",
    },
    output: {
        path: path.resolve(__dirname, './build'),
        filename: "mech.js" // <--- Will be compiled to this single file
    },
    resolve: {
        extensions: [".ts", ".js"],
        fallback: { "timers": require.resolve("timers-browserify") }
    },
    module: {
        rules: [
            {
                test: /\.tsx?$/,
                loader: "ts-loader"
            }
        ]
    },
    optimization: {
        minimize: false,
    },
    // Other rules...
	plugins: [
		new NodePolyfillPlugin()
	]
};