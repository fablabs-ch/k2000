<template>
  <v-btn color="primary" @click="tare()">Primary</v-btn>
</template>

<script>
export default {
  name: 'settings',
  methods: {
    tare: function () {
      this.$http.get('/').then(response => {
        console.log('Ça marcheeee.')
      }, response => {
        console.log('Ça marche paaaaas.')
      })
    }
  }
}
</script>

<style>

</style>

