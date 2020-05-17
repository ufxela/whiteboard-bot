// todo: make fn to break up a points string into bite sized chunks and another fn to send those chunks
export const API_URL = "";
export const MAX_REQ_BODY = 512; // can probably be larger
export const MAX_PTS_STR_LEN = MAX_REQ_BODY - 10; // allot space for metadata

function onError(e) {
    console.error(e);
}

export function getPointsString(saveData){
    saveData = JSON.parse(saveData);
    console.log(saveData, typeof(saveData));
    let pointsString = "";

    for(const line of saveData.lines){
        pointsString += 'p,'; // p for place
        for(const point of line.points){
            // optionally: sample every Nth point to reduce data amount
            // alternatively: calculate offsets, since we know should mostly be continuous
            // as a result, we can reduce on data.
            // alternatively: don't store as strings, store as actual int data.
            pointsString += `${Math.round(point.x)},${Math.round(point.y)},`
        }
        pointsString += 'l,'; // l for lift
    }
    return pointsString;
}

function not_complete_coord(pointsString){
    const commas_count = (pointsString.match(/,/g) || []).length;
    const lift_place_count = (pointsString.match(/l/g) || []).length + (pointsString.match(/p/g) || []).length;
    if((commas_count - lift_place_count) % 2 === 1){
        // odd # of commas => even number of coordinate elements, and we want an even # b/c two coordinate elements per coordinate 
        return true;
    }else{
        return false;
    }
}

export function breakDownPointsString(pointsString){
    const len = pointsString.length;
    let pointsStrings = [];
    let curr_start = 0;
    let curr_end = MAX_PTS_STR_LEN;

    while(curr_start < len){
        if(curr_end > len){
            curr_end = len;
        }else{
            while(pointsString.charAt(curr_end - 1) !== "," || not_complete_coord(pointsString.substring(curr_start, curr_end))){
                curr_end--;
                if(curr_end <= curr_start){
                    console.log("ERROR");
                    return null;
                }
            }
        }

        pointsStrings.push(pointsString.substring(curr_start, curr_end));
        curr_start = curr_end;
        curr_end += MAX_PTS_STR_LEN;
    }
    
    return pointsStrings;
}

/**
 * 
 * @param {*} pointsString 
 * @param {*} currentStringIndex 
 * @param {*} totalStrings 
 * 
 * data string format: currentStringIndex,totalStrings,[l|p|INT]*
 */
export async function sendPoints(pointsString, currentStringIndex, totalStrings) {
    const dataString = `${currentStringIndex},${totalStrings},${pointsString}`;
    
    if(dataString.length > MAX_REQ_BODY){
        return {success: false, response: "request too large"}
    }
    try {
        console.log("Sending data string:", dataString);
        const response = await fetch(`${API_URL}/points`, {
            method: 'POST',
            body: dataString
        }).then(e => e.text());
        // console.log(response);
        const res = {
            success: true,
            response: response,
        }
        return res;
    } catch (e) {
        onError(e);
    }
}