const path = require('path');
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
        alias: {
            "@root": path.join(__dirname, "src"),
            "@tasks": path.join(__dirname, "src", "tasks"),
            "@trees": path.join(__dirname, "src", "trees"),
            "@blackboards": path.join(__dirname, "src", "blackboards"),
            "@decorators": path.join(__dirname, "src", "decorators"),
            "@predicates": path.join(__dirname, "src", "predicates"),
            "@branches": path.join(__dirname, "src", "branches"),
            "@utility": path.join(__dirname, "src", "utility"),
        }
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