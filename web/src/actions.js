export const API_URL = "";

function onError(e) {
    console.error(e);
    // alert("Error");
}

export async function peripheralWrite(number, value) {
    try {
        const data = { number, value };
        console.log("peripheral write", data);
        const response = await fetch(`${API_URL}/peripheral_write`, {
            method: 'post',
            body: JSON.stringify(data)
        }).then(e => e.text());
        console.log(response);
        return response;
    } catch (e) {
        onError(e);
    }
}

export async function peripheralRead(number) {
    try {
        const data = { number };
        console.log("peripheral read", data);
        const response = await fetch(`${API_URL}/peripheral_read`, {
            method: 'post',
            body: JSON.stringify(data)
        }).then(e => e.text());
        return Number(response);
    } catch (e) {
        onError(e);
        return null;
    }
}

export async function poll() {
    try {
        console.log("poll");
        const response = await fetch(`${API_URL}/poll`).then(e => e.json());
        console.log(response);
        return response;
    } catch (e) {
        onError(e);
    }
}

export async function executeBin(formData) {
    try {
        console.log("execute bin");
        const response = await fetch(`${API_URL}/execute_bin`, {
            method: 'POST',
            body: formData
        }).then(e => e.text());
        console.log(response);
        return response;
    } catch (e) {
        onError(e);
    }
}