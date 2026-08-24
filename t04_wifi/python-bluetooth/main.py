
import threading
import time
import socket
import subprocess

def bluetooth_devices():

    subprocess.run(["bluetoothctl", "power", "on"])
    subprocess.run(["bluetoothctl", "scan", "on"])
    time.sleep(5)
    subprocess.run(
        ["bluetoothctl", "scan", "off"],
        capture_output=True
    )

    result = subprocess.run(
        ["bluetoothctl", "devices"],
        capture_output=True,
        text=True
    )

    devices = []

    for line in result.stdout.splitlines():
        parts = line.split(" ", 2)

        if len(parts) == 3 and parts[0] == "Device":
            mac = parts[1]
            name = parts[2]

            devices.append({
                "name": name,
                "mac": mac
            })

    return devices

def find_device(devices, name):
    for device in devices:
        if device["name"].lower() == name.lower():
            return device

    return None

def connect_by_name(devices, name):
    device = find_device(devices, name)

    if not device:
        print(f"Device not found: {name}")
        return None

    mac = device["mac"]

    print(f"Connecting to {name} ({mac})...")

    sock = socket.socket(
        socket.AF_BLUETOOTH,
        socket.SOCK_STREAM,
        socket.BTPROTO_RFCOMM
    )

    try:
        sock.connect((mac, 1))
        print("Connected successfully!")

        return sock

    except OSError as e:
        print(f"Connection failed: {e}")
        sock.close()
        return None


def read_bluetooth(sock):

    try:
        while True:
            data = sock.recv(1024)

            if not data:
                print("\nBluetooth disconnected.")
                break

            message = data.decode("utf-8", errors="replace").strip()

            print(f"\nESP32 → {message}")
            print("> ", end="", flush=True)

    except OSError as e:
        print(f"\nBluetooth read error: {e}")

def main():
    devices = bluetooth_devices()

    if not devices:
        print("No Bluetooth devices found.")
        return

    print("\nBluetooth devices:")

    for device in devices:
        print(f"- {device['name']} [{device['mac']}]")

    name = input("\nEnter Bluetooth device name: ").strip()

    sock = connect_by_name(devices, name)

    if sock:
         # Start Bluetooth reader
        reader = threading.Thread(
            target=read_bluetooth,
            args=(sock,),
            daemon=True
        )

        reader.start()

        try:
            while True:
                command = input("> ")
                if command.lower() == "exit":
                    sock.close()
                    return

                sock.sendall(
                    (command + "\n").encode("utf-8")
                )

        except (OSError, BrokenPipeError):
            print("\nConnection lost.")

        finally:
            try:
                sock.close()
            except OSError:
                pass

        print("Scanning again...")
        time.sleep(2)

if __name__ == "__main__":
    main()