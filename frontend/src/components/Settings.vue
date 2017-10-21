<template>
  <div>
    <v-btn color="primary" @click="tare()">Primary</v-btn>
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
export default {
  name: 'settings',
  data: function () {
    return {
      snackbar: false,
      snacktext: ''
    }
  },
  methods: {
    tare: function () {
      this.$http.get('/').then(response => {
        this.notify('Ça marcheeee.')
      }, response => {
        this.notify('Ça ne marche pas.')
      })
    },
    notify: function (message) {
      this.snacktext = message
      this.snackbar = true
    }
  }
}
</script>

<style>

</style>

