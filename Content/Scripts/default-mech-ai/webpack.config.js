const path = require('path');

module.exports = {
    mode: "development",
    devtool: false,
    entry: {
        main: "./src/mech.ts",
    },
    output: {
        path: path.resolve(__dirname, './build'),
        filename: "mech.js" // <--- Will be compiled to this single file
    },
    resolve: {
        extensions: [".ts", ".js"],
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
        minimize: true,
    },
};