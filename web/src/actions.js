// todo: make fn to break up a points string into bite sized chunks and another fn to send those chunks
export const API_URL = "";

function onError(e) {
    console.error(e);
}

export function getPointsString(saveData){
    saveData = JSON.parse(saveData);
    console.log(saveData, typeof(saveData));
    
    for(const line of saveData.lines){
        for(const point of line.points){
            console.log("point", point);
        }
    }
    return "unimplemented";
}

export async function sendPoints(pointsString) {
    try {
        console.log("Sending points string:", pointsString);
        const response = await fetch(`${API_URL}/points`, {
            method: 'post',
            body: pointsString
        }).then(e => e.text());
        console.log(response);
        const res = {
            success: true,
            response: response,
        }
        return res;
    } catch (e) {
        onError(e);
    }
}