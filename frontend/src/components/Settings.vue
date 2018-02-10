<template>
  <div>

    <v-btn color="primary" @click="tare()">Tare</v-btn>
    <v-btn color="error" @click="stop()">Stop</v-btn>

    <ingredientConfig v-for="item in config" :item='item' :key="item.id"></ingredientConfig>

    <v-snackbar :timeout=2000
                :top=true
                :vertical=true
                v-model="snackbar">
      {{ snacktext }}
      <v-btn flat color="pink" @click.native="snackbar = false">Close</v-btn>
    </v-snackbar>
  </div>
</template>

<script>
import IngredientConfig from './IngredientConfig'

export default {
  name: 'settings',
  components: {
    IngredientConfig
  },
  data () {
    return {
      snackbar: false,
      snacktext: '',
      config: []
    }
  },
  methods: {
    tare () {
      this.$http.post('api/command/tare').then(response => {
        this.notify('Tare sent')
      }, response => {
        this.notify('Error when trying to tare')
      })
    },
    stop () {
      this.$http.post('api/command/stop').then(response => {
        this.notify('Stop sent')
      }, response => {
        this.notify('Error when trying to stop')
      })
    },
    notify (message) {
      this.snacktext = message
      this.snackbar = true
    }
  },
  mounted () {
    // this.config = [{'id': 10, 'ingredient': 12}, {'id': 12, 'ingredient': 11}]
    this.$http.get('api/config').then(response => {
      this.config = response.data
    }, response => {
      this.notify('Impossible to load the config')
    })
  }
}
</script>

<style>

</style>

