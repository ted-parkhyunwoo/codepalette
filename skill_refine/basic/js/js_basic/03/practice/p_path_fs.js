const path = require('path');
const fs = require('fs');

const current_dir_path = path.dirname(__filename);
const file_name = "example.txt";
const file_path = path.join(current_dir_path, file_name);

let new_data = "!!!NEW DATA!!!"

fs.readFile(file_path, "utf8", (err, data) => {
    if (err) {
        // make new file if err.
        console.log(`[WARN] can't find file. make new one: ${file_name}.`);
        fs.writeFile(file_path, new_data, () => {});
    } else {
        console.log(`${file_name} found.`);
        // write new_data
        const tmp = `${data}\n${new_data}`;
        fs.writeFile(file_path, tmp, ()=>{});
        console.log("OK.")
    }
})