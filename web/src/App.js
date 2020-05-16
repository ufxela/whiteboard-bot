import './App.css';

import { getPointsString, sendPoints } from './actions';

import CanvasDraw from "react-canvas-draw";
import React from 'react';

const App = () => {
  let canvasRef;
  
  async function onCanvasSubmit(){
    if(canvasRef){
      const res = await sendPoints(getPointsString(canvasRef.getSaveData()));
      if(res.success){
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
