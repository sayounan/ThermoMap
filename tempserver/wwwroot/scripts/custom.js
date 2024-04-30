let canvas;
let ctx;

window.initializeCanvas = () => {
    canvas = document.getElementById('overlayCanvas');
    ctx = canvas.getContext('2d');
}
window.handleImageClick = (clientX, clientY) => {
    const image = document.getElementById('sagittalImage');
    const rect = image.getBoundingClientRect();
    const x = clientX - rect.left;
    const y = clientY - rect.top;

    // Clear previous drawings
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // Draw a box at the clicked position
    ctx.strokeStyle = 'red';
    ctx.lineWidth = 2;
    ctx.strokeRect(x - 25, y - 25, 50, 50); // Adjust box dimensions as needed
}
