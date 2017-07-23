// Create the element

var script = document.createElement("script");

// Add script content

script.innerHTML = "setTimeout(function(){ window.close() }, 10000);";

// Append

document.body.appendChild(script);
