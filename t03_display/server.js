const http = require("http");
const { URL } = require("url");

const server = http.createServer((req, res) => {

    const url = new URL(req.url, `http://${req.headers.host}`);

    if (req.method === "GET" && url.pathname === "/") {

        const device = url.searchParams.get("device");
        const temp = url.searchParams.get("temp");
        const humidity = url.searchParams.get("humidity");

        console.log("========== ESP32 ==========");
        console.log("Device   :", device);
        console.log("Temp     :", temp);
        console.log("Humidity :", humidity);
        console.log("===========================");

        const response = {
            success: true,
            message: "Data received",
            device: device,
            temp: temp,
            humidity: humidity
        };

        res.writeHead(200, {
            "Content-Type": "application/json"
        });

        res.end(JSON.stringify(response));
        return;
    }

    res.writeHead(404, {
        "Content-Type": "text/plain"
    });

    res.end("Not Found");
});

server.listen(8080, "0.0.0.0", () => {
    console.log("Server running at http://0.0.0.0:8080");
});