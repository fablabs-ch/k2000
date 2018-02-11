<template>
 <v-dialog :value="order" max-width="80%">
     <v-stepper v-model="step">
      <v-stepper-header>
        <v-stepper-step step="1" :complete="step > 1">Prepare Glass</v-stepper-step>
        <v-divider></v-divider>
        <v-stepper-step step="2" :complete="step > 2">Mixing</v-stepper-step>
        <v-divider></v-divider>
        <v-stepper-step step="3">Ready</v-stepper-step>
      </v-stepper-header>
      <v-stepper-content step="1">
        <v-layout justify-center>
          <cocktail-loader message="Please put your glass in the machine"></cocktail-loader>
        </v-layout>
        <v-layout row>
          <v-spacer></v-spacer>
          <v-btn flat @click.native="reset">Cancel</v-btn>
          <v-btn color="primary" @click.native="executeOrder">Glass OK</v-btn>
        </v-layout>
      </v-stepper-content>
      <v-stepper-content step="2">
        <v-layout justify-center>
          <cocktail-loader message="Please wait while we fill up your glass... Stream status from backend?" :run="true"></cocktail-loader>
        </v-layout>
        <v-layout>
          <v-btn color="error" @click.native="stop">STOP</v-btn>
          <v-spacer></v-spacer>
          <v-btn color="primary" @click.native="step = 3">DONE</v-btn>
        </v-layout>
      </v-stepper-content>
      <v-stepper-content step="3">
          Bla blab,
          <v-layout justify-center v-if="order && order.shakeYourBody">
            <img class="shake" src="../assets/shaker.svg" alt="shaker">
          </v-layout>
        <v-layout>
          <v-spacer></v-spacer>
          <v-btn color="primary" @click.native="reset">Close</v-btn>
        </v-layout>
      </v-stepper-content>
    </v-stepper>
 </v-dialog>
</template>

<script>
import CocktailLoader from '@/components/CocktailLoader'

export default {
  props: ['order'],
  data () {
    return {
      step: 1
    }
  },
  methods: {
    reset () {
      this.step = 1
      this.$emit('close')
    },
    stop () {
      this.$http.get('command/stop').then(response => {
        this.reset()
      }, response => {
        this.$root.notify('Error when trying to stop')
      })
    },
    executeOrder () {
      this.$http.post('command/order', this.order.items.filter(i => !i.disabled)).then(response => {
        this.step = 2
      }, response => {
        this.$root.notify('Error when trying to order. Is machine free? Currently backend does not support queue.')
      })
    }
  },
  components: {
    CocktailLoader
  }
}
</script>

<style>
@keyframes shake {
	0% { transform: translate(2px, 1px) rotate(0deg); }
	10% { transform: translate(-1px, -2px) rotate(-1deg); }
	20% { transform: translate(-3px, 0px) rotate(1deg); }
	30% { transform: translate(0px, 2px) rotate(0deg); }
	40% { transform: translate(1px, -1px) rotate(1deg); }
	50% { transform: translate(-1px, 2px) rotate(-1deg); }
	60% { transform: translate(-3px, 1px) rotate(0deg); }
	70% { transform: translate(2px, 1px) rotate(-1deg); }
	80% { transform: translate(-1px, -1px) rotate(1deg); }
	90% { transform: translate(2px, 2px) rotate(0deg); }
	100% { transform: translate(1px, -2px) rotate(-1deg); }
}
.shake {
	animation-name: shake;
	animation-duration: 0.8s;
	transform-origin:50% 50%;
	animation-iteration-count: infinite;
	animation-timing-function: linear;
  width: 200px;

}
</style>
