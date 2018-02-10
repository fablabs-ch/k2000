<template>
  <div>

    <v-btn color="primary" @click="tare()">Tare</v-btn>
    <v-btn color="error" @click="stop()">Stop</v-btn>

    <ingredientConfig v-for="item in config" :item='item' :key="item.id"></ingredientConfig>

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
      config: []
    }
  },
  methods: {
    tare () {
      this.$http.post('command/tare').then(response => {
        this.$root.notify('Tare sent')
      }, response => {
        this.$root.notify('Error when trying to tare')
      })
    },
    stop () {
      this.$http.post('command/stop').then(response => {
        this.$root.notify('Stop sent')
      }, response => {
        this.$root.notify('Error when trying to stop')
      })
    }
  },
  mounted () {
    // this.config = [{'id': 10, 'ingredient': 12}, {'id': 12, 'ingredient': 11}]
    this.$http.get('config').then(response => {
      this.config = response.data
    }, response => {
      this.$root.notify('Impossible to load the config')
    })
  }
}
</script>

<style>

</style>

