// CommonJS
const { user, user1 } = require("./user.js");
const hello = require("./hello.js");


// ES
// import user from "./user.js";
// import { user, user1 } from "./user.js";     // 여러개
// import hello from "./hello.js";

hello(user);
hello(user1);