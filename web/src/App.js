import './App.css';

import { breakDownPointsString, getPointsString, reboot, sendPoints } from './actions';

import CanvasDraw from "react-canvas-draw";
import React from 'react';

const App = () => {
  let canvasRef;
  
  async function onCanvasSubmit(){
    if(canvasRef){
      let success = false;
      const pointsStrings = breakDownPointsString(getPointsString(canvasRef.getSaveData()));
      for(let i = 0; i < 1 /*pointsStrings.length*/; i++){
        let res = await sendPoints(pointsStrings[i], i, pointsStrings.length);
        success &= true; // lol
      }
      if(success){
        canvasRef.clear();
      }else{
        alert("there was an error in sending your points");
      }
    }
  }

  function onCanvasClear(){
    if(canvasRef){
      canvasRef.clear();
    }
  }

  async function onReboot(){
    await reboot();
    alert("pi rebooting");
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
