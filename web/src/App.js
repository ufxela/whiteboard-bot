import './App.css';

import React, { useState } from 'react';
import { breakDownPointsString, getPointsString, reboot, sendPoints } from './actions';

import CanvasDraw from "react-canvas-draw";

const App = () => {
  const [prevPointsString, setPrevPointsString] = useState("");

  let canvasRef;
  
  async function onCanvasSubmit(){
    if(canvasRef){
      let success = true;
      const pointsString = getPointsString(canvasRef.getSaveData());

      // only send the new points in the canvas
      let newPointsString = pointsString;
      console.log("prev points string", prevPointsString, "new points string", newPointsString);
      if(pointsString.indexOf(prevPointsString) !== 0){
        alert("previous points not subsequence of current points! Try clearing canvas");
        return;
      }else{
        newPointsString = pointsString.substring(prevPointsString.length);
      }

      // break down into bite sized pieces because ESP is finnicky.
      const pointsStringPieces = breakDownPointsString(newPointsString);
      for(let i = 0; i < 1 /*pointsStrings.length*/; i++){
        await sendPoints(pointsStringPieces[i], i, pointsStringPieces.length);
        success &= true; // lol 
      }
      
      if(success){
        setPrevPointsString(pointsString);
        alert("your canvas was sent!");
      }else{
        alert("there was an error in sending your points");
      }
    }
  }

  function onCanvasClear(){
    if(canvasRef){
      canvasRef.clear();
    }
    setPrevPointsString("");
  }

  async function onReboot(){
    await reboot();
    setPrevPointsString("");
    if(canvasRef){
      canvasRef.clear();
    }
    alert("reboot command sent!");

  }
  
  return ( 
    <div>
      <CanvasDraw 
        hideInterface
        hideGrid
        lazyRadius={0}
        brushRadius={1}
        canvasWidth={1000}
        canvasHeight={700}
        ref={canvasDraw => (canvasRef = canvasDraw)}
      /> 
      <button onClick={onCanvasSubmit}>
        send
      </button>
      <button onClick={onCanvasClear}>
        clear
      </button>
      <button onClick={onReboot}>
        reboot
      </button>
    </div>
  );
}

export default App;
