export const API_URL = "";
export const MAX_REQ_BODY = 512; // can probably be larger
export const MAX_PTS_STR_LEN = MAX_REQ_BODY - 10; // allot space for metadata

function onError(e) {
    console.error(e);
}

/**
 * Current ways to increase data efficiency:
 * - stores relative offsets, instead of absolute data. Note: first data point is always absolute.
 *   (saves between 3x and 100x amount of data, depending on a variety of factors)
 * 
 * Other ways to increase data efficiency: 
 * - sample every Nth point (~N times more efficient), or coalesce series of small offsets into single larger offset
 * - store as actual int data, not strings (~25.6 times more efficient)
 * 
 */ 
export function getPointsString(saveData){
    saveData = JSON.parse(saveData);
    console.log(saveData, typeof(saveData));
    let pointsString = "";

    let prev_x = 0, prev_y = 0;
    for(const line of saveData.lines){
        pointsString += 'p,'; // p for place
        for(const point of line.points){
            let curr_x = Math.round(point.x);
            let curr_y = Math.round(point.y);
            if(curr_x - prev_x !== 0 && curr_y - prev_y !== 0){
                // only send data if non zero.
                pointsString += `${curr_x - prev_x},${curr_y - prev_y},`
                prev_x = curr_x;
                prev_y = curr_y;
            }
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

export async function reboot(){
    try {
        const response = await fetch(`${API_URL}/poll`, {
            method: 'GET',
        }).then(e => e.text());
        const res = {
            success: true,
            response: response,
        }
        return res;
    } catch (e) {
        onError(e);
    }
}