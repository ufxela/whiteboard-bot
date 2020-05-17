import './App.css';

import { breakDownPointsString, getPointsString, sendPoints } from './actions';

import CanvasDraw from "react-canvas-draw";
import React from 'react';

const App = () => {
  let canvasRef;
  
  async function onCanvasSubmit(){
    if(canvasRef){
      let success = false;
      const pointsStrings = breakDownPointsString(getPointsString(canvasRef.getSaveData()));
      for(let i = 0; i < pointsStrings.length; i++){
        let res = await sendPoints(pointsStrings[i], i, pointsStrings.length);
        success &= res.success;
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
    </div>
  );
}

export default App;
