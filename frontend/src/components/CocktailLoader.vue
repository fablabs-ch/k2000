/* adapted from https://codepen.io/MarcMalignan/pen/svLux */
<template>
  <div class="cocktail-loader">
      <div class="loader">
          <div :class="{show: loaded === 100}" class="lemon"></div>
          <div :class="{show: loaded === 100}" class="straw"></div>
          <div class="glass" :class="{animate: !run}">
              <div class="cubes">
                  <div :class="{show: loaded >= 25}"></div>
                  <div :class="{show: loaded >= 50}"></div>
                  <div :class="{show: loaded >= 75}"></div>
              </div>
              <div class="drink" :style="{top: `${100 - loaded * .9}%`}"></div>
              <span class="counter" v-show="run">{{loaded}}%</span>
          </div>
          <div class="coaster"></div>
      </div>
      <footer>{{message}}</footer>
  </div>
</template>

<script>
export default {
  props: ['message', 'run'],
  data () {
    return {
      loaded: 0,
      intervalWorker: null
    }
  },
  mounted () {
    if (this.run) {
      this.startLoading()
    }
  },
  methods: {
    startLoading () {
      this.loaded = 0
      this.intervalWorker = setInterval(this.increment, 30)
    },
    stopLoading () {
      if (this.intervalWorker) {
        clearInterval(this.intervalWorker)
      }
    },
    increment () {
      if (this.loaded === 100) {
        this.stopLoading()
        setTimeout(this.startLoading, 1000)
      } else {
        this.loaded++
      }
    }
  },
  watch: {
    run (val) {
      this.stopLoading()
      if (val) {
        this.startLoading()
      }
    }
  }
}
</script>

<style scoped>

.show {
  opacity: 1 !important;
}

.glass.animate {
  animation-duration: 2s;
  animation-name: glass;
  animation-iteration-count: infinite;
}

@keyframes glass {
  0% {
    bottom: 100px
  }

  80% {
    bottom: 0px;
  }
}

.cocktail-loader {
  position: relative;
  width: 320px;
  height: 320px;
  text-align: center;
  background: radial-gradient(ellipse at center, rgb(172, 170, 170) 0%,rgba(255, 255, 255, 0) 70%);
}

.loader {
    position: absolute;
    top:50%; left:50%;
    height:200px; width:100px;
    margin-top:-100px; margin-left:-50px;
}

.glass {
    position: relative;
    height: 100%;
    background: rgba(255,255,255,.1);
    border-radius: 0% 0% 15% 15%;
    border: 3px solid;
    border-top: 0;
    border-bottom: 20px solid;
    border-color: rgba(255,255,255,.7);
    overflow: hidden;
}
.drink {
    position: absolute;
    top:100%; right:0; bottom:0; left:0;
    background: linear-gradient(to bottom, orange, orangered);
    box-shadow: inset 0 2px 1px rgba(255,69,0,.2);
    opacity: .7;
}
.counter {
    position: relative;
    line-height: 200px;
    font-size: 22px;
    color: rgba(255,255,255,1);
}

.lemon {
    position: absolute;
    top:0; right:0;
    height:79px; width:79px;
    margin-top:-38px; margin-right:-38px;
    background: radial-gradient(#f7f3b6 10%, #d7d26c);
    border-radius: 50%;
    border: 4px solid #47582e;
    box-shadow: inset 0 0 0 2px #f7f3b6;
    transition: opacity 200ms ease-in-out;
    opacity: 0;
}
.straw {
    position: absolute;
    bottom:20px; right:30%;
    height:220px; width:6px;
    background: steelblue;
    border-radius: 0 6px 0 0;
    transform: rotate(-18.5deg);
    transform-origin: left bottom;
    transition: opacity 300ms ease-in-out;
    opacity: 0;
}
.straw:after {
    content: '';
    position: absolute;
    top:0; right:0;
    height:6px; width:80px;
    background: inherit;
    border-radius: 0 6px 0 0;
}

.cubes {
    position: absolute;
    top:0; right:0; bottom:0; left:0;
}
.cubes div {
    position: absolute;
    width:50px; height:50px;
    background: rgba(255,255,255,.3);
    border-radius: 10px;
    box-shadow: inset 0 0 10px rgba(255,255,255,.6);
    transition: opacity 100ms ease-in-out;
    opacity: 0;
}
.cubes div:nth-child(1) {
    bottom:0;
}
.cubes div:nth-child(2) {
    bottom:45px; left:25px;
    transform: rotate(32deg);
    transform-origin: center bottom;
}
.cubes div:nth-child(3) {
    bottom:90px; left:20px;
    transform: rotate(-34deg);
    transform-origin: center bottom;
}

.coaster {
    width: 130%; height: 4px;
    margin-left: -15%;
    background: steelblue;
    border-radius: 2px;
}

footer {
    position: absolute;
    left:0; top:50%; right:0;
    margin-top: 120px;
    color: steelblue;
}
</style>
