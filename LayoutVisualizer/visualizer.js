// Key Options read from constants.json file
var keyOptions = [
    " ",
    "FUNC_LAYER",
    "KEY_ESC",
    "KEY_F1",
    "KEY_F2",
    "KEY_F3",
    "KEY_F4",
    "KEY_F5",
    "KEY_F6",
    "KEY_F7",
    "KEY_F8",
    "KEY_F9",
    "KEY_F10",
    "KEY_F11",
    "KEY_F12",
    "KEY_TAB",
    "KEY_CAPS_LOCK",
    "KEY_LEFT_SHIFT",
    "KEY_LEFT_CTRL",
    "KEY_LEFT_GUI",
    "KEY_LEFT_ALT",
    "KEY_RIGHT_SHIFT",
    "KEY_RIGHT_CTRL",
    "KEY_RIGHT_GUI",
    "KEY_RIGHT_ALT",
    "KEY_UP_ARROW",
    "KEY_DOWN_ARROW",
    "KEY_LEFT_ARROW",
    "KEY_RIGHT_ARROW",
    "KEY_HOME",
    "KEY_END",
    "KEY_INSERT",
    "KEY_DELETE",
    "KEY_BACKSPACE",
    "KEY_RETURN",
    "`",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "0",
    "-",
    "=",
    "q",
    "w",
    "e",
    "r",
    "t",
    "y",
    "u",
    "i",
    "o",
    "p",
    "[",
    "]",
    "\\",
    "a",
    "s",
    "d",
    "f",
    "g",
    "h",
    "j",
    "k",
    "l",
    ";",
    "'",
    "z",
    "x",
    "c",
    "v",
    "b",
    "n",
    "m",
    ",",
    ".",
    "/"
];


// Initial Config Data
let config = [[["KEY_ESC","KEY_F1","KEY_F2","KEY_F3","KEY_F4","KEY_F5","KEY_F6"," ","3"," "," "," "],["`","1","2","3","4","5","6","7","8"," "," "," "],["KEY_TAB","q","w","e","r","t","y","u","i"," "," "," "],["KEY_CAPS_LOCK","a","s","d","f","g","h","j","k"," "," "," "],["KEY_LEFT_SHIFT","z","x","c","v","b","n","m",","," "," "," "]]];

const layerSelect = document.getElementById("layerSelect");
const layerContainer = document.getElementById("layerContainer");
const configOutput = document.getElementById("configOutput");
const rowsInput = document.getElementById("rowsInput");
const colsInput = document.getElementById("colsInput");
const loadFile = document.getElementById("loadFile");

// Render Layers
function renderLayers() {
    var oldLayerSelectValue = layerSelect?.value;
    layerSelect.innerHTML = "";
    layerContainer.innerHTML = "";
    config.forEach((layer, layerIndex) => {
        const option = document.createElement("option");
        option.value = layerIndex;
        option.textContent = `Layer ${layerIndex + 1}`;
        layerSelect.appendChild(option);
        if(oldLayerSelectValue == null || oldLayerSelectValue == undefined || oldLayerSelectValue == "") {
            oldLayerSelectValue = layerSelect.firstChild.value; 
        }
        layerSelect.value = oldLayerSelectValue;
        
        // Always render all layers, but only show the selected layer content
        const layerDiv = document.createElement("div");
        layerDiv.style.display = layerIndex === parseInt(oldLayerSelectValue) ? 'block' : 'none';
        renderLayer(layerDiv, layer, oldLayerSelectValue);
        layerContainer.appendChild(layerDiv);
    });
}

function renderLayer(layerDiv, layer, layerIndex) {
    const grid = document.createElement("div");
    grid.className = "grid";
    grid.style.gridTemplateColumns = `repeat(${layer[0].length}, auto)`;

    layer.forEach((row, rowIndex) => {
        row.forEach((key, colIndex) => {
        const select = document.createElement("select");
        keyOptions.forEach((option) => {
            const opt = document.createElement("option");
            opt.value = option;
            opt.textContent = option;
            if (option === key) opt.selected = true;
            select.appendChild(opt);
        });
        select.dataset.layer = layerIndex;
        select.dataset.row = rowIndex;
        select.dataset.col = colIndex;
        select.addEventListener("change", handleInputChange);
        grid.appendChild(select);
        });
    });

    layerDiv.appendChild(grid);
}


function handleInputChange(e) {
  const layer = e.target.dataset.layer;
  const row = e.target.dataset.row;
  const col = e.target.dataset.col;
  config[layer][row][col] = e.target.value;
}

// Add Layer
document.getElementById("addLayer").addEventListener("click", () => {
  const numRows = parseInt(rowsInput.value);
  const numCols = parseInt(colsInput.value);
  const newLayer = Array.from({ length: numRows }, () => Array(numCols).fill(" "));
  config.push(newLayer);
  renderLayers();
});

// Remove Layer
document.getElementById("removeLayer").addEventListener("click", () => {
  const selectedLayer = parseInt(layerSelect.value);
  if (config.length > 1) {
    config.splice(selectedLayer, 1);
    layerSelect.value = layerSelect.lastChild.value - 1;
    renderLayers();
  } else {
    alert("Cannot remove the last layer.");
  }
});

// Update Layout
document.getElementById("updateLayout").addEventListener("click", () => {
  const selectedLayer = parseInt(layerSelect.value);
  const numRows = parseInt(rowsInput.value);
  const numCols = parseInt(colsInput.value);

  const currentLayer = config[selectedLayer];
  const newLayer = Array.from({ length: numRows }, (_, rowIndex) =>
    Array.from({ length: numCols }, (_, colIndex) =>
      currentLayer[rowIndex] && currentLayer[rowIndex][colIndex] ? currentLayer[rowIndex][colIndex] : " "
    )
  );

  config[selectedLayer] = newLayer;
  renderLayers();
});

// Generate Config
document.getElementById('generateConfig').addEventListener('click', () => {
let output = 'int AllLayers[NumLayers][NumRows][NumCols] = {\n';
config.forEach((layer, layerIndex) => {
    output += `  // Layer ${layerIndex + 1}\n  {\n`;
    layer.forEach((row) => {
    output += `    {${row
        .map((key) => {
        // Reserved keys (uppercase, underscores, and numbers) stay unquoted
        if (key.startsWith('KEY_') || key.startsWith('FUNC_')) {
            return key;
        }
        // Non-reserved keys are wrapped in single quotes
        return `'${key}'`;
        })
        .join(', ')}},\n`;
    });
    output += '  },\n';
});
output += '};';
configOutput.value = output;
});

// Save Config
document.getElementById("saveConfig").addEventListener("click", () => {
  const blob = new Blob([JSON.stringify(config)], { type: "application/json" });
  const url = URL.createObjectURL(blob);
  const a = document.createElement("a");
  a.href = url;
  a.download = "keyboard_config.json";
  a.click();
  URL.revokeObjectURL(url);
});

// Load Config
document.getElementById("loadConfig").addEventListener("click", () => {
  loadFile.click();
});

loadFile.addEventListener("change", (e) => {
  const file = e.target.files[0];
  if (file) {
    const reader = new FileReader();
    reader.onload = (event) => {
      try {
        config = JSON.parse(event.target.result);
        renderLayers();
      } catch (error) {
        alert("Invalid file format.");
      }
    };
    reader.readAsText(file);
  }
});

// Initial Render
layerSelect.addEventListener("change", () => {
  renderLayers();
});

renderLayers();